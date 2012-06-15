#include "command.h"
#include <dlfcn.h>
#include <iostream>

typedef Command*(*commandLoader)();

Command::Command()
{
}

GOptionGroup *Command::options() const
{
  return NULL;
}

Command *Command::loadCommand(std::string name)
{
  Command *cmd = loadCommandLibrary("./"+name+".so");
  if (!cmd)
    cmd = loadCommandLibrary("/usr/libexec/bzt/"+name+".so");
  return cmd;
}

Command *Command::loadCommandLibrary(std::string path)
{
  void *module = dlopen(path.c_str(), RTLD_NOW);
  if (!module) {
    return 0;
  }

  commandLoader modFunc = (commandLoader)dlsym(module, "_bzt_make_command");
  if (!modFunc) {
    dlclose(module);
    std::cerr << "Error loading " << path.c_str() << ": " << dlerror() << std::endl;
    return 0;
  }

  Command *cmd = modFunc();
  return cmd;
}
