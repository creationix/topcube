#include <v8.h>
#include <node.h>
#include <gtk/gtk.h>
#include <webkit/webkitwebview.h>

using namespace node;
using namespace v8;

static Handle<Value> main_quit(const Arguments& args) {
  gtk_main_quit();
  return Undefined();
}


static Handle<Value> create_window(const Arguments& args)
{
  HandleScope scope;

  if (args.Length() < 1 || !args[0]->IsString()) {
    return ThrowException(Exception::TypeError(String::New("Url Required")));
  }

  String::Utf8Value url(args[0]->ToString());
  
  GtkWidget *window;
  GtkWidget *scrolled_window;
  GtkWidget *web_view;

  gtk_init (NULL, NULL);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  scrolled_window = gtk_scrolled_window_new (NULL, NULL);
  web_view = webkit_web_view_new ();

  gtk_container_add (GTK_CONTAINER (scrolled_window), web_view);
  gtk_container_add (GTK_CONTAINER (window), scrolled_window);
  
  webkit_web_view_load_uri (WEBKIT_WEB_VIEW (web_view), *url);

  gtk_window_set_default_size (GTK_WINDOW (window), 1024, 768);
  gtk_widget_show_all (window);

  // TODO: find a way to not block the node event loop
  gtk_main ();

  return Undefined();

}

extern "C" {
  static void init(Handle<Object> target)
  {
    NODE_SET_METHOD(target, "mainQuit", main_quit);
    NODE_SET_METHOD(target, "createWindow", create_window);
  }

  NODE_MODULE(webapp, init);
}
