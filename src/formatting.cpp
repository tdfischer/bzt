#include "formatting.h"
#include <iostream>
#include "bug.h"

void printBugTree(const Bug &root, int depth)
{
  std::vector<Bug> blockers = root.blockedBugs();
  if (blockers.size() > 0 && depth == 0) {
    std::vector<Bug>::iterator it;
    for(it = blockers.begin(); it != blockers.end();it++) {
      printBugTree(*it);
    }
  } else {
    for(int i = 0;i<depth;i++)
      std::cout << " ";
    std::cout << root.severity() << ": " << root.id() << " - " << root.title() << std::endl;
    std::vector<Bug> bugs = root.dependencies();
    std::vector<Bug>::iterator it;
    for(it = bugs.begin(); it!= bugs.end();it++) {
      printBugTree(*it, depth+1);
    }
  }
}
