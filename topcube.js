var modpath = __dirname + "/build/default/topcube_native.node";
var ChildProcess = require('child_process');
module.exports = function WebApp(url, callback) {
  // TODO: Fix native bindings to not block the node event loop so this won't be needed
  var command = process.execPath + " -e " + 
      "'require(" + JSON.stringify(modpath) + ").createWindow(" + JSON.stringify(url) + ");'";
  ChildProcess.exec(command, callback);
};
