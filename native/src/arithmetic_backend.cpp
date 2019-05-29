#include "arithmetic_backend.hpp"

namespace homomorphine {

  //
  // Backend class implementation
  //

  void ArithmeticBackend::setParams(map<string, string> &params) 
  {
    this->params.clear();
    this->params.insert(params.begin(), params.end());
  }

  map<string, string> ArithmeticBackend::getParams() 
  {
    return this->params;
  } 

  string ArithmeticBackend::getParam(string key) 
  {
    return this->params[key];
  }

  void ArithmeticBackend::setParam(string &key, string &value) 
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