#!/usr/bin/env node

var Http = require('http'),
    Stack = require('stack'),
    Creationix = require('creationix'),
    TopCube = require('../lib/index');

var client = TopCube({
  url: 'http://localhost:7569',
  name: 'Creationix',
  width: 800,
  height: 600
});

if (client) {
    Http.createServer(Stack(
      Creationix.log(),
      Creationix.static("/", __dirname + "/www", "index.html")
    )).listen(7569);
} else {
    console.log('topcube client failed to start')
}
