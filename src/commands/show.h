#ifndef SHOW_H
#define SHOW_h

#include "../command.h"

class Show : public Command {
  public:
    int exec(std::vector<std::string> args);
};

EXPORT_COMMAND(Show)

#endif //COMMAND_H
