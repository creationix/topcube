#!/usr/bin/env node

var Http = require('http'),
    Stack = require('stack'),
    Creationix = require('creationix'),
    TopCube = require('topcube');

var PORT = 7569;
var handler = Stack(
  Creationix.log(),
  Creationix.static("/", __dirname + "/www")
);
(function listen() {
  try {
    Http.createServer(handler).listen(PORT);
  } catch (err) {
    if (err.code === "EADDRINUSE") {
      PORT++;
      listen();
      return;
    }
    throw err;
  }
  TopCube("http://127.0.0.1:" + PORT + "/index.html");
}());

