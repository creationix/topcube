#ifdef __APPLE__

#include <iostream>
int main(int argc, char* argv[])
{
    std::clog << "OS X is not currently supported by topcube\n";
    return 0;
}

#else

#include <string.h> // for strcmp
#include <cstdlib> // for exit
#include <gtk/gtk.h>
#include <webkit/webkit.h>
#include <webkit/webkitwebview.h>

GtkWidget *window;
GtkWidget *scrolled_window;
GtkWidget *web_view;
WebKitWebSettings *settings;

void destroy (void)
{
  gtk_main_quit ();
}

void title_change (void)
{
  gtk_window_set_title(GTK_WINDOW (window), webkit_web_view_get_title(WEBKIT_WEB_VIEW (web_view)));
}

void new_window (
  WebKitWebView *web_view,
  WebKitWebFrame *frame,
  WebKitNetworkRequest *request)
{
  gchar *argv[3];
  argv[0] = const_cast<char*>("/usr/bin/xdg-open");
  argv[1] = const_cast<char*>(webkit_network_request_get_uri(request));
  argv[2] = NULL;
  g_spawn_async(NULL, argv, NULL, G_SPAWN_LEAVE_DESCRIPTORS_OPEN, NULL, NULL, NULL, NULL);
}

static gboolean download (
  WebKitWebView *web_view,
  WebKitWebFrame *frame,
  WebKitNetworkRequest *request,
  const char *mime_type,
  WebKitWebPolicyDecision *decision,
  gpointer user_data)
{
  // Any other mime types we should handle?
  if (strcmp(mime_type, "text/html") != 0) {
    WebKitDownload *download = webkit_download_new(request);
    GtkWidget *window = gtk_widget_get_toplevel (GTK_WIDGET(web_view));
    GtkWidget *dialog = gtk_file_chooser_dialog_new ("Save file",
      GTK_WINDOW(window),
      GTK_FILE_CHOOSER_ACTION_SAVE,
      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
      GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
      NULL);
    gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER (dialog), TRUE);
    gtk_file_chooser_set_current_name (GTK_FILE_CHOOSER (dialog), webkit_download_get_suggested_filename(download));

    // @TODO getting a warning 'Unable to retrieve the file info' for the
    // file as it does not exist yet... track down why?
    if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT) {
      gchar *destination = g_filename_to_uri(gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog)), NULL, NULL);
      webkit_download_set_destination_uri (download, destination);
      webkit_download_start(download);
      g_free(destination);
    } else {
      webkit_download_cancel(download);
      g_object_unref(download);
    }

    gtk_widget_destroy (dialog);
    webkit_web_policy_decision_ignore(decision);
  }
  return TRUE;
}

int main(int argc, char* argv[])
{
  static gchar *url = const_cast<char*>("http://google.com");
  static gchar *name = const_cast<char*>("TopCube");
  static gint width = 800;
  static gint height = 600;
  static gint minwidth = 600;
  static gint minheight = 400;
  static GOptionEntry entries[] = {
    { "url", 'u', 0, G_OPTION_ARG_STRING, &url, "URL", NULL },
    { "name", 'n', 0, G_OPTION_ARG_STRING, &name, "Window name", NULL },
    { "width", 'W', 0, G_OPTION_ARG_INT, &width, "Width", NULL },
    { "height", 'H', 0, G_OPTION_ARG_INT, &height, "Height", NULL },
    { "minwidth", 'w', 0, G_OPTION_ARG_INT, &minwidth, "Minimum width", NULL },
    { "minheight", 'h', 0, G_OPTION_ARG_INT, &minheight, "Minimum height", NULL }
  };
  GError *error = NULL;
  GOptionContext *options;
  options = g_option_context_new("topcube options");
  g_option_context_add_main_entries (options, entries, NULL);
  g_option_context_add_group (options, gtk_get_option_group(TRUE));
  if (!g_option_context_parse (options, &argc, &argv, &error)) {
    g_print ("Error parsing options: %s\n", error->message);
    exit (1);
  }

  gtk_init (&argc, &argv);
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  scrolled_window = gtk_scrolled_window_new (NULL, NULL);
  web_view = webkit_web_view_new ();

  // Modify default settings - disable right click menus.
  settings = webkit_web_view_get_settings (WEBKIT_WEB_VIEW(web_view));
  g_object_set(settings, "enable-default-context-menu", FALSE, NULL);

  gtk_signal_connect (GTK_OBJECT (window), "destroy", GTK_SIGNAL_FUNC (destroy), NULL);
  gtk_signal_connect (GTK_OBJECT (web_view), "title-changed", GTK_SIGNAL_FUNC (title_change), NULL);
  gtk_signal_connect (GTK_OBJECT (web_view), "mime-type-policy-decision-requested", GTK_SIGNAL_FUNC (download), NULL);
  gtk_signal_connect (GTK_OBJECT (web_view), "new-window-policy-decision-requested", GTK_SIGNAL_FUNC (new_window), NULL);

  gtk_container_add (GTK_CONTAINER (scrolled_window), web_view);
  gtk_container_add (GTK_CONTAINER (window), scrolled_window);

  webkit_web_view_load_uri (WEBKIT_WEB_VIEW (web_view), url);

  gtk_window_set_wmclass (GTK_WINDOW (window), name, name);
  gtk_window_set_default_size (GTK_WINDOW (window), width, height);

  GdkGeometry hints;
  hints.min_width = minwidth;
  hints.min_height = minheight;
  gtk_window_set_geometry_hints(GTK_WINDOW (window), GTK_WIDGET (scrolled_window), &hints, GDK_HINT_MIN_SIZE);

  gtk_widget_grab_focus (GTK_WIDGET(web_view));
  gtk_widget_show_all (window);
  gtk_main ();

  return 0;
}


#endif // linux
