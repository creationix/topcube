import os
import sys
import urllib
import tarfile

source_url = sys.argv[1]
target_file = os.path.abspath(sys.argv[2])
dirname = os.path.abspath(sys.argv[3])

if not os.path.exists(target_file):
    urllib.urlretrieve(source_url, target_file)

tfile = tarfile.open(target_file,'r:gz');
tfile.extractall(dirname)
sys.exit(0)
