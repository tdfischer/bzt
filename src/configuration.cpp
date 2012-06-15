#include "configuration.h"
#include <unistd.h>
#include <fstream>
#include <yaml-cpp/node.h>
#include <yaml-cpp/parser.h>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

Configuration::Configuration()
{
  char cwd[1024];
  std::ifstream file;
  std::string configName = ".bzt.yaml";
  getcwd(cwd, sizeof(cwd));
  std::vector<std::string> components;

  boost::algorithm::split(components, cwd, boost::algorithm::is_any_of("/"));
  do {
    std::string path = boost::algorithm::join(components, "/");
    file.open(path+"/.bzt.yaml");
    components.pop_back();
    if (file.good()) {
      YAML::Parser parser(file);
      YAML::Node config;
      parser.GetNextDocument(config);
      m_configs.push_back(config.Clone());
    }
  } while (components.size() > 0);
}

std::string Configuration::getString(const std::string &key, const std::string &defaultValue)
{
  if (m_configs.size() == 0)
    return defaultValue;

  std::vector<std::auto_ptr<YAML::Node>>::iterator it;
  for(it = m_configs.begin(); it != m_configs.end(); it++) {
    const YAML::Node *value = (*it)->FindValue(key);
    if (value) {
      std::string ret;
      *value >> ret;
      return ret;
    }
  }
  return defaultValue;
}
