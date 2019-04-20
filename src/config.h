#include <boost/foreach.hpp>
#include <string>
#include <map>
#include <exception>
#include <iostream>
#include <boost/log/trivial.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "interface.h"

namespace pt = boost::property_tree;

#ifndef _MORPHINE_CONFIG_H_
#define _MORPHINE_CONFIG_H_

using namespace std;

namespace Morphine 
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
  };
}

#endif