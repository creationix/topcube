# WebApp

In the pursuit of making a gui toolkit for node and in a goal to better learn how to make node bindings, I present my first node extension, WebApp.

This is very much a work in progress.

## Goals

Give node developers a way to have a desktop GUI to their node servers using HTML5 + CSS3 as the GUI platform.

## Implementation Details

Currently I'm using webkitgtk since it comes with my linux desktop and is easy to bind to.

## TODOS

 - Share the event loop between GTK's GLib and Node's libev.  Tim Smart's node-gtk binding seems to implement this.
   - I'm running the webview in a child process currently as a workaround.
 - Provide a way for the JavaScript in the webview talk to the JavaScript in node.
   - Currently we can use websockets or normal ajax.
   - It would be neat if webkit got it's contexts from node's V8
 - provide some infrastructure to get html to the browser. Currently the sample app shows how this can be done app-side.

