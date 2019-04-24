#include <string>
#include <map>
#include <iostream>
#include <exception>
#include <boost/algorithm/string.hpp>

using namespace std;

#ifndef _MORPHINE_BACKEND_H_
#define _MORPHINE_BACKEND_H_

namespace Morphine 
{
  
  class Backend
  {
    protected:
      map<string, string> params;

    public:
      virtual ~Backend() {}
      virtual void setAlgorithm(string algorithm) {}
      virtual void init() {}

      map<string, string> getParams();
      void setParams(map<string, string> &params); 
      string getParam(string key);
      void  setParam(string &key, string &value);
  };

  class BackendException : public std::exception 
  {
	  private:
      const char* msg;

    public:
      BackendException(const char* msg);

      const char* getMessage();
  };

}

#endif