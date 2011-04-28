#!/usr/bin/env node

var Stack = require('stack'),
    Creationix = require('creationix'),
    TopCube = require('topcube');

TopCube(Stack(
  Creationix.log(),
  Creationix.static("/", __dirname + "/www", "index.html")
));

