var spawn = require('child_process').spawn;
var path = require('path');

module.exports = function (options) {
    options = options || {};
    options.url = options.url || 'http://nodejs.org';
    options.name = options.name || 'nodejs';

    var client;
    switch (process.platform) {
    case 'win32':
        client = path.resolve(__dirname + '/cefclient/cefclient');
        break;
    case 'linux':
        client = path.resolve(__dirname + '/build/default/topcube');
        break;
    default:
        console.warn('');
        return null;
        break;
    }

    var args = [];
    for (var key in options) args.push('--' + key + '=' + options[key]);

    var child = spawn(client, args);
    child.on('exit', function(code) {
        process.exit(code);
    });
    child.stdout.pipe(process.stdout);
    child.stderr.pipe(process.stderr);
    return child;
};

