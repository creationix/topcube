#include <v8.h>
#include <node.h>
#include <gtk/gtk.h>
#include <webkit/webkitwebview.h>

// stl for n00b debugging :)
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
// std::clog << "debug output";

using namespace node;
using namespace v8;

GtkWidget *window;
GtkWidget *scrolled_window;
GtkWidget *web_view;

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

static Handle<Value> create_window(const Arguments& args)
{
  HandleScope scope;

  if (args.Length() != 3) {
    return ThrowException(Exception::TypeError(String::New("`url`, `width`, and `height` arguments are required")));
  }
  if (!args[0]->IsString()) {
    return ThrowException(Exception::TypeError(String::New("`url` must be a string")));
  }
  if (!args[1]->IsInt32()) {
    return ThrowException(Exception::TypeError(String::New("`width` must be an int32")));
  }
  if (!args[2]->IsInt32()) {
    return ThrowException(Exception::TypeError(String::New("`height` must be an int32")));
  }

  String::Utf8Value url(args[0]->ToString());
  int width = args[1]->Int32Value();
  int height = args[2]->Int32Value();

  gtk_init (NULL, NULL);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  scrolled_window = gtk_scrolled_window_new (NULL, NULL);
  web_view = webkit_web_view_new ();

  gtk_signal_connect (GTK_OBJECT (window), "destroy", GTK_SIGNAL_FUNC (destroy), NULL);
  gtk_signal_connect (GTK_OBJECT (web_view), "title-changed", GTK_SIGNAL_FUNC (title_change), NULL);
  gtk_signal_connect (GTK_OBJECT (web_view), "new-window-policy-decision-requested", GTK_SIGNAL_FUNC (new_window), NULL);

  gtk_container_add (GTK_CONTAINER (scrolled_window), web_view);
  gtk_container_add (GTK_CONTAINER (window), scrolled_window);

  webkit_web_view_load_uri (WEBKIT_WEB_VIEW (web_view), *url);

  gtk_window_set_default_size (GTK_WINDOW (window), width, height);
  gtk_widget_show_all (window);

  // TODO: find a way to not block the node event loop
  gtk_main ();
  return Undefined();

}

extern "C" {
  static void init(Handle<Object> target)
  {
    NODE_SET_METHOD(target, "createWindow", create_window);
  }

  NODE_MODULE(topcube_native, init);
}
