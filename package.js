var exec = require('child_process').exec;
switch (process.platform) {
case 'win32':
    console.log('win32: Downloading CEF client...');
    exec('curl -skL https://github.com/downloads/mapbox/cefclient/cefclient-0.0.2.tar.gz | tar zx', function(err, stdout, stderr) {
        console.log(stdout);
        console.log(stderr);
        return err ? process.exit(1) : process.exit(0);
    });
    break;
case 'linux':
    exec('node-waf clean || true; node-waf configure build', function(err, stdout, stderr) {
        console.log(stdout);
        console.log(stderr);
        return err ? process.exit(1) : process.exit(0);
    });
    break;
default:
    console.log('Topcube currently does not support %s', process.platform);
    return process.exit(0);
    break;
}
