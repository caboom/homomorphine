#ifndef _HOMOMORPHINE_CONFIG_H_
#define _HOMOMORPHINE_CONFIG_H_

#include <boost/foreach.hpp>
#include <string>
#include <map>
#include <exception>
#include <iostream>
#include <boost/log/trivial.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "interface.hpp"

using namespace std;

namespace pt = boost::property_tree;

namespace homomorphine 
{
  /*! /brief Configuration for Homomorphine service.
   *
   * This class provides a configuration for Homomorphine service wrapper.
   */
  class Config 
  {
    private: 
      map<string, Interface> interfaces;                   /*!< map of interfaces service is supposed to run on */
      friend ostream& operator<<(ostream&, const Config&);

    public:
      ~Config(); 

      /*!
       * Initialize configuration from JSON file.
       * 
       * \param file path to JSON file
       */
      void init(string &file);

      /*!
       * Returns the configured interfaces.
       * 
       * \return map of interfaces
       */
      map<string, Interface> getInterfaces();

      /*!
       * Returns the number of interfaces.
       * 
       * \return number of interfaces
       */
      int interfacesSize();
  };
}

#endif