var ChildProcess = require('child_process'),
    Http = require('http');

module.exports = function WebApp(handler) {

  var PORT = 7569;
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
  }());

  var url = "http://127.0.0.1:" + PORT + "/";
  var child = ChildProcess.spawn(process.execPath, [__dirname + "/client.js", url]);
  child.on('exit', function (code) {
    process.exit(code);
  });
  child.stdout.pipe(process.stdout);
  child.stderr.pipe(process.stderr);
};
