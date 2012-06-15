#ifndef TASKLIST_H
#define TASKLIST_H

#include "../command.h"

class TaskList : public Command {
  public:
    GOptionGroup *options() const;
    int exec(std::vector<std::string> args);
};

EXPORT_COMMAND(TaskList)

#endif //TASKLIST_H
