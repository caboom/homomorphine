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

}