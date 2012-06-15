#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <string>
#include <yaml-cpp/node.h>
#include <memory>

class Configuration {
  public:
    Configuration();
    std::string getString(const std::string &key, const std::string &defaultValue = "");
  private:
    std::vector<std::auto_ptr<YAML::Node>> m_configs;
};

#endif //CONFIGURATION_H
