#include "backend.hpp"

namespace Morphine {
  
  void Backend::setParams(map<string, string> &params) 
  {
    this->params = params;
  }

  map<string, string> Backend::getParams() 
  {
    return this->params;
  } 

  string Backend::getParam(string key) 
  {
    return this->params[key];
  }

  void Backend::setParam(string &key, string &value) 
  {
    this->params[key] = value;
  }

  BackendException::BackendException(const char* msg) 
  {
    this->msg = msg;
  }

  const char* BackendException::getMessage() {
    return this->msg;
  }  

}