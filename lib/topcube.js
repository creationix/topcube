var spawn = require('child_process').spawn;
var path = require('path');

module.exports = function (options) {
    options = options || {};
    options.url = options.url || 'http://nodejs.org';
    options.name = options.name || 'nodejs';

    var client;
    var keys = [];
    switch (process.platform) {
    case 'win32':
        client = path.resolve(__dirname + '/../bin/cefclient/cefclient');
        keys = ['url', 'name', 'width', 'height', 'minwidth', 'minheight', 'ico', 'cache-path', 'log-file'];
        break;
    case 'linux':
        client = path.resolve(__dirname + '/../bin/topcube');
        keys = ['url', 'name', 'width', 'height', 'minwidth', 'minheight'];
        break;
    default:
        console.warn('');
        return null;
        break;
    }

    var args = [];
    for (var key in options) {
        if (keys.indexOf(key) !== -1) {
            args.push('--' + key + '=' + options[key]);
        }
    }

    var child = spawn(client, args);
    child.on('exit', function(code) {
        process.exit(code);
    });
    child.stdout.pipe(process.stdout);
    child.stderr.pipe(process.stderr);
    return child;
};

