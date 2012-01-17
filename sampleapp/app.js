#!/usr/bin/env node

var Http = require('http'),
    Stack = require('stack'),
    Creationix = require('creationix'),
    TopCube = require('../topcube.js');

Http.createServer(Stack(
  Creationix.log(),
  Creationix.static("/", __dirname + "/www", "index.html")
)).listen(7569);

TopCube({
  url: 'http://localhost:7569',
  name: 'Creationix',
  width: 800,
  height: 600
});

