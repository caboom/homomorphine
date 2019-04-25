#include <boost/foreach.hpp>
#include <string>
#include <map>
#include <exception>
#include <iostream>
#include <boost/log/trivial.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "interface.hpp"

namespace pt = boost::property_tree;

using namespace std;

#ifndef _HOMOMORPHINE_CONFIG_H_
#define _HOMOMORPHINE_CONFIG_H_

namespace Homomorphine 
{
  struct debug_settings
  {
    
  };

  class Config 
  {
    private: 
      map<string, Interface> interfaces;
      friend std::ostream& operator<<(std::ostream&, const Config&);

    public:
      ~Config();

      void init(string &file);
      map<string, Interface> getInterfaces();
      int interfacesSize();
  };
}

#endif