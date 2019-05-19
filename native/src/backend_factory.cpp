#include "backend_factory.hpp"

namespace homomorphine 
{

  //
  // BackendFactory class implementation
  //

  Backend* BackendFactory::create(string type)
  {
    return create(getType(type));
  }

  Backend* BackendFactory::create(BackendType type)
  {
    if (type == B_SEAL) {
      return new SealBackend();
    } 
    else if (type == B_HELib) {
      return new HELibBackend();
    } 

    throw BackendFactoryException("Unknown/unsupported backend type");
  }
  
  BackendType BackendFactory::getType(string name) {
    boost::algorithm::to_lower(name);

    if (name == "seal") return B_SEAL;
    if (name == "helib") return B_HELib;

    return B_UNKNOWN;
  } 

  //
  // BackendFactoryException class implementation
  //

  BackendFactoryException::BackendFactoryException(const char* msg) 
  {
    this->msg = msg;
  }

  const char* BackendFactoryException::getMessage() {
    return this->msg;
  }  
}