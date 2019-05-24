#include "backend.hpp"

namespace homomorphine {

  //
  // Backend class implementation
  //

  void Backend::setParams(map<string, string> &params) 
  {
    this->params.clear();
    this->params.insert(params.begin(), params.end());
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

  //
  // BackendException class implementation
  //

  BackendException::BackendException(const char* msg) 
  {
    this->msg = msg;
  }

  const char* BackendException::getMessage() {
    return this->msg;
  }  

  //
  // BackendOperationNotSupported class implementation
  //

  BackendOperationNotSupported::BackendOperationNotSupported(const char* msg) 
  {
    this->msg = msg;
  }

  const char* BackendOperationNotSupported::getMessage() {
    return this->msg;
  }

}