# WebApp

In the pursuit of making a gui toolkit for node and in a goal to better learn how to make node bindings, I present my first node extension, WebApp.

This is very much a work in progress and I'm not even sure if it will stay active.

## Goals

Give node developers a way to have a desktop GUI to their node servers using HTML5 + CSS3 as the GUI platform.

## Implementation Details

Currently I'm using webkitgtk since it comes with my linux desktop and is easy to bind to.

## TODOS

 - Share the event loop between GTK's GLib and Node's libev.  Tim Smart's node-gtk binding seems to implement this.
 - Provide a way for the JavaScript in the webview talk to the JavaScript in node.
   - Maybe they should share a context, maybe not.  Sharing a context would require replacing the JavaScriptCore in the webview with node's V8 instance.
   - Sharing a context could prove very dangerous.
   - How about instead, we simply provide two-way messaging.  Though that could also expose nasty security holes.
 - Provide a way for node to populate the content of the webview.  This may be a local http server or some other means.

