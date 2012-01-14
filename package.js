var exec = require('child_process').exec;
switch (process.platform) {
case 'win32':
    console.log('win32: Downloading CEF client...');
    exec('curl -skL https://github.com/downloads/mapbox/cefclient/cefclient-0.0.1.tar.gz | tar zx', function(err) {
        if (err) return process.exit(1);
        console.log('win32: CEF client downloaded successfully.')
        process.exit(0);
    });
    break;
default:
    exec('node-waf clean || true; node-waf configure build', function(err) {
        if (err) return process.exit(1);
        process.exit(0);
    });
}
