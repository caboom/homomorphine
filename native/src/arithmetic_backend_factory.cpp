#include "arithmetic_backend_factory.hpp"

namespace homomorphine 
{

  //
  // BackendFactory class implementation
  //

  ArithmeticBackend* ArithmeticBackendFactory::create(string name)
  {
    return create(getType(name));
  }

  ArithmeticBackend* ArithmeticBackendFactory::create(ArithmeticBackendType type)
  {
    #ifdef __HAS_SEAL__
    if (type == B_SEAL) {
      return new SealBackend();
    }
    #endif

    #ifdef __HAS_HELIB__
    if (type == B_HELib) {
      return new HELibBackend();
    } 
    #endif

    throw ArithmeticBackendFactoryException("Unknown/unsupported backend type");
  }
  
  ArithmeticBackendType ArithmeticBackendFactory::getType(string name) {
    boost::algorithm::to_lower(name);

    #ifdef __HAS_SEAL__
    if (name == "seal") return B_SEAL;
    #endif
    
    #ifdef __HAS_HELIB__
    if (name == "helib") return B_HELib;
    #endif

    return B_UNKNOWN;
  } 

  //
  // BackendFactoryException class implementation
  //

  ArithmeticBackendFactoryException::ArithmeticBackendFactoryException(const char* msg) 
  {
    this->msg = msg;
  }

  const char* ArithmeticBackendFactoryException::getMessage() {
    return this->msg;
  }  
}