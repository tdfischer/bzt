#include "bug.h"
#include "client.h"
#include <iostream>

class BugPrivate {
  public:
    BugPrivate(xmlrpc_c::value_struct values, Client *client);
    BugPrivate(int id, Client *client);
    void loadData(xmlrpc_c::value_struct values);
    bool loaded;
    int id;
    std::string title;
    std::string severity;
    std::vector<int> depends;
    std::vector<int> blocked;
    Client *client;
};

BugPrivate::BugPrivate(int id, Client *client)
  : id(id)
  , loaded(false)
  , client(client)
{
}

BugPrivate::BugPrivate(xmlrpc_c::value_struct values, Client *client)
  : client(client)
{
  loadData(values);
}

Bug::Bug(int id, Client *client)
  : m_d(new BugPrivate(id, client))
{
  refresh();
}

void Bug::refresh()
{
  std::vector<int> bugList;
  bugList.push_back(m_d->id);
  std::vector<Bug> newBug = m_d->client->get(bugList);
  m_d = newBug[0].m_d;
}

void BugPrivate::loadData(xmlrpc_c::value_struct values)
{
  bzArgs args = values;
  id = xmlrpc_c::value_int(args["id"]);
  title = xmlrpc_c::value_string(args["summary"]);
  severity = xmlrpc_c::value_string(args["severity"]);
  {
    std::vector<xmlrpc_c::value> deps = xmlrpc_c::value_array(args["depends_on"]).vectorValueValue();
    std::vector<int> bugList;
    std::vector<xmlrpc_c::value>::iterator it;
    for(it = deps.begin();it != deps.end();it++) {
      bugList.push_back(xmlrpc_c::value_int(*it));
    }
    depends = bugList;
  }
  {
    std::vector<xmlrpc_c::value> blockers = xmlrpc_c::value_array(args["blocks"]).vectorValueValue();
    std::vector<int> bugList;
    std::vector<xmlrpc_c::value>::iterator it;
    for(it = blockers.begin();it != blockers.end();it++) {
      bugList.push_back(xmlrpc_c::value_int(*it));
    }
    blocked = bugList;
  }
  loaded = true;
}

Bug::Bug(xmlrpc_c::value_struct values, Client *client)
  : m_d(new BugPrivate(values, client))
{
}

int Bug::id() const
{
  return m_d->id;
}

std::vector<Bug> Bug::dependencies() const
{
  return m_d->client->get(m_d->depends);
}

std::vector<Bug> Bug::blockedBugs() const
{
  return m_d->client->get(m_d->blocked);
}

std::string Bug::title() const
{
  return m_d->title;
}

Bug::Bug(const Bug &other)
{
  m_d = other.m_d;
}

std::string Bug::severity() const
{
  return m_d->severity;
}
