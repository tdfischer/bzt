#ifndef CLIENT_H
#define CLIENT_H
#include <xmlrpc-c/client.hpp>
#include <xmlrpc-c/client_transport.hpp>
#include <vector>
#include "bug.h"

typedef std::map<std::string, xmlrpc_c::value> bzArgs;

class Client;

class bzSearch {
  public:
    bzSearch();
    void addField(std::string field, xmlrpc_c::value value);
    bzArgs toArgs() const;
  private:
    bzArgs m_args;
};

class Client {
  public:
    Client(std::string rpcURL);
    bool login(std::string username, std::string password);
    std::vector<Bug> search(bzSearch params);
    std::vector<Bug> get(std::vector<int> idList);

  private:
    bzArgs call(std::string method, bzArgs args);
    xmlrpc_c::clientXmlTransport *m_transport;
    xmlrpc_c::carriageParm *m_carriage;
    std::vector<Bug> m_cache;
};

#endif // CLIENT_H

