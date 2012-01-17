import Options
from os import unlink, symlink, popen
from os.path import exists

srcdir = "."
blddir = "build"
VERSION = "0.0.1"

def set_options(opt):
  opt.tool_options("compiler_cxx")

def configure(conf):
  conf.check_tool("compiler_cxx")
  conf.check_cfg(package='gtk+-2.0', uselib_store='GTK', args='--cflags --libs')
  conf.check_cfg(package='glib-2.0', args='--cflags --libs', uselib_store='GLIB')
  conf.check_cfg(package='webkit-1.0', args='--cflags --libs', uselib_store='WEBKIT')

def build(bld):
  obj = bld.new_task_gen("cxx", "program")
  obj.target = "topcube"
  obj.source = "topcube.cpp"
  obj.cxxflags = ["-D_FILE_OFFSET_BITS=64", "-D_LARGEFILE_SOURCE"]
  obj.uselib = "GTK GLIB WEBKIT"

def shutdown():
  if Options.commands['clean']:
    if exists('topcube'): unlink('topcube')

