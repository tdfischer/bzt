#include "client.h"
#include <iostream>

Client::Client(std::string rpcURL)
{
  m_carriage = new xmlrpc_c::carriageParm_curl0(rpcURL);
  m_transport = new xmlrpc_c::clientXmlTransport_curl;
}

bool Client::login(std::string username, std::string password)
{
  bzArgs args;
  args["login"] = xmlrpc_c::value_string(username);
  args["password"] = xmlrpc_c::value_string(password);
  call("User.login", args);
  return true;
}

std::vector<Bug> Client::search(bzSearch params)
{
  bzArgs args = params.toArgs();
  bzArgs result = call("Bug.search", args);
  std::vector<xmlrpc_c::value> bugList = xmlrpc_c::value_array(result["bugs"]).vectorValueValue();
  std::vector<xmlrpc_c::value>::iterator it;
  std::vector<Bug> ret;
  for(it = bugList.begin(); it!= bugList.end(); it ++) {
    ret.push_back(Bug(xmlrpc_c::value_struct(*it), this));
  }
  return ret;
}

std::vector<Bug> Client::get(std::vector<int> idList)
{
  std::vector<Bug> ret;
  if (idList.size() == 0)
    return ret;
  bzArgs args;
  std::vector<xmlrpc_c::value> arrayData;
  std::vector<int>::iterator idit;
  for(idit = idList.begin(); idit != idList.end();idit++) {
    std::vector<Bug>::iterator cacheIt;
    bool found = false;
    for(cacheIt = m_cache.begin();cacheIt != m_cache.end() && !found;cacheIt++) {
      if (cacheIt->id() == *idit) {
        found = true;
        ret.push_back(*cacheIt);
      }
    }
    if (!found) {
      arrayData.push_back(xmlrpc_c::value_int(*idit));
    }
  }
  args["ids"] = xmlrpc_c::value_array(arrayData);
  args["permissive"] = xmlrpc_c::value_boolean(true);

  bzArgs result = call("Bug.get", args);
  std::vector<xmlrpc_c::value> bugList = xmlrpc_c::value_array(result["bugs"]).vectorValueValue();
  std::vector<xmlrpc_c::value>::iterator it;
  for(it = bugList.begin(); it!= bugList.end(); it ++) {
    Bug b = Bug(xmlrpc_c::value_struct(*it), this);
    ret.push_back(b);
    m_cache.push_back(b);
  }
  return ret;
}

bzArgs Client::call(std::string method, bzArgs args)
{
  xmlrpc_c::paramList params;
  params.add(xmlrpc_c::value_struct(args));
  xmlrpc_c::rpcPtr rpc(method, params);
  xmlrpc_c::client_xml client(m_transport);
  rpc->call(&client, m_carriage);
  return xmlrpc_c::value_struct(rpc->getResult());
}

bzSearch::bzSearch()
{
}

bzArgs bzSearch::toArgs() const
{
  return m_args;
}

void bzSearch::addField(std::string field, xmlrpc_c::value value)
{
  m_args[field] = value;
}
