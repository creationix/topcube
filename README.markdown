TopCube
-------
Gives node developers a way to have a desktop GUI to their node servers using HTML5 + CSS3 as the GUI platform.

Assumes:

- **Client/server architecture with communication over HTTP.**  
  If you're interested in merged event loops, common javascript contexts, or other non-HTTP communication and resource sharing between the node process and the GUI take a look at [node-webkit](https://github.com/rogerwang/node-webkit).
- **Single, HTML5 + CSS3 driven window.**  
  The client window does not spawn popups, support tabs, create additional windows or add any native UI components other than what a typical browser pane would provide.
- **Child process.**  
  The client window runs as a child process of the calling node process.

## Implementation Details

**Linux**

Requires `gtk2.0` and `webkitgtk`. Install the following packages on Debian/Ubuntu or the equivalents for your system to build topcube:

    sudo apt-get install libgtk2.0-dev libwebkitgtk-dev

**Windows**

The windows client currently downloads a custom compiled binary client that uses the [Chromium Embedded Framework](http://code.google.com/p/chromiumembedded/). If you're interested in building the client yourself or making modifications see [mapbox/cefclient](https://github.com/mapbox/cefclient).

**Mac OS X**

TODO. Work on a native webkit client for Mac OS X that can be built within topcube is certainly welcome.

## API

Pass a single `options` object to topcube with the following properties:

- `url` of your running node application to point topcube at.
- `name` of the window displayed in the titlebar. Also sets any window manager classes associated with the topcube window. On linux a `.desktop` file using the same name can be used set the icon for your application.
- `width` in pixels of the window. Optional.
- `height` in pixels of the windows. Optional.
- `minwidth` in pixels. Restricts resizing the window width smaller than this value. Optional.
- `minheight` in pixels. Restricts resizing the window height smaller than this value. Optional.
- `ico` full path to a Windows `.ico` file to use for your application. Optional, no-op on non-windows platforms.

Example usage of topcube to wrap a default "Hello world" server.

    var Http = require('http');
    var TopCube = require('topcube');

    Http.createServer(function (req, res) {
      res.writeHead(200, {'Content-Type': 'text/plain'});
      res.end('Hello World\n');
    }).listen(7569);

    TopCube({
      url: 'http://localhost:7569',
      name: 'My webapp',
      width: 800,
      height: 600
    });

