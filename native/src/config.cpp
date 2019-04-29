#include "config.hpp"

namespace homomorphine 
{
  Config::~Config() 
  {
    this->interfaces.clear();
  }

  void Config::init(string &file) 
  {
    pt::ptree tree;
    pt::read_json(file, tree);

    // network interface configuration, including homomorphic backend
    BOOST_FOREACH(pt::ptree::value_type &value, tree.get_child("interfaces")) {
      Interface interface;

      interface.setHost(value.second.get_child("").get<string>("host"));
      interface.setPort(value.second.get_child("").get<int>("port"));
      interface.setProtocol(value.second.get_child("").get<string>("protocol"));
      interface.setBackend(value.second.get_child("").get<string>("backend"));

      this->interfaces[value.first] = interface;
    }
  }

  map<string, Interface> Config::getInterfaces() 
  {
    return this->interfaces;
  }

  int Config::interfacesSize() 
  {
    return this->interfaces.size();
  }

  std::ostream& operator<<(std::ostream &strm, const Config &config) 
  {
    for (auto& [key, value] : config.interfaces) {
      strm << "interface: " <<  key << endl;
      strm << value;
    }
    
    return strm;
  }
  
}