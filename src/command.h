#ifndef COMMAND_H
#define COMMAND_H

#include <glib.h>
#include <vector>
#include <string>

class Client;

class Command {
  public:
    static Command *loadCommand(std::string name);
    static Command *loadCommandLibrary(std::string path);
    Command();
    Client client() const;
    virtual GOptionGroup *options() const;
    virtual int exec(std::vector<std::string> args) = 0;
};

#define EXPORT_COMMAND(commandClass) \
  extern "C" {Command *_bzt_make_command() {return new commandClass;}}

#endif //COMMAND_H
