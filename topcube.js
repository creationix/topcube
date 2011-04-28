var modpath = __dirname + "/build/default/topcube_native.node";
var ChildProcess = require('child_process');
module.exports = function WebApp(url) {
  // TODO: Fix native bindings to not block the node event loop so this won't be needed
  var child = ChildProcess.spawn(process.execPath, [__dirname + "/client.js", url]);
  child.on('exit', function (code) {
    process.exit(code);
  });
  return child;
};
