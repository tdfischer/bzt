#include "show.h"
#include "../client.h"
#include "../bug.h"
#include "../configuration.h"
#include <iostream>

int Show::exec(std::vector<std::string> args)
{
  Configuration config;
  Client c(config.getString("url"));
  std::vector<int> bugIDList;
  std::vector<std::string>::iterator it;
  for(it = args.begin(); it != args.end(); it++) {
    int bugNum = atoi(it->c_str());
    if (bugNum > 0)
      bugIDList.push_back(bugNum);
    else
      std::cerr << *it << " is not a valid bug number." << std::endl;
  }

  std::vector<Bug> bugList = c.get(bugIDList);

  if (bugList.size() == 0) {
    std::cout << "Zarro boogs found." << std::endl;
    return 1;
  }
  {
    std::vector<Bug>::iterator it;
    for(it = bugList.begin();it != bugList.end(); it++) {
      std::cout << "#" << it->id() << " - " << it->title() << std::endl;
    }
  }
  return 0;
}
