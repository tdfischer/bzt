#ifndef BUG_H
#define BUG_H

#include <xmlrpc-c/client.hpp>
#include <vector>
#include <memory>

class BugPrivate;
class Client;

class Bug {
  public:
    Bug();
    Bug(const Bug &other);
    explicit Bug(int id, Client *client);
    explicit Bug(xmlrpc_c::value_struct values, Client *client);
    int id() const;
    std::vector<Bug> dependencies() const;
    std::vector<Bug> blockedBugs() const;
    std::string title() const;
    std::string severity() const;
    void refresh();
  private:
    std::shared_ptr<BugPrivate> m_d;
};


#endif // BUG_H
