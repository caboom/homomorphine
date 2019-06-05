#include "boolean_circuit_backend_factory.hpp"

namespace homomorphine 
{

  //
  // BooleanCircuitBackendFactory class implementation
  //

  BooleanCircuitBackend* BooleanCircuitBackendFactory::create(string name)
  {
    return create(getType(name));
  }

  BooleanCircuitBackend* BooleanCircuitBackendFactory::create(BooleanCircuitBackendType type)
  {

    #ifdef __HAS_TFHE__
    if (type == BooleanCircuitBackendType::TFHE) {
      return new TFHEBackend();
    } 
    #endif

    throw BooleanCircuitBackendFactoryException("Unknown/unsupported backend type");
  }
  
  BooleanCircuitBackendType BooleanCircuitBackendFactory::getType(string name) {
    boost::algorithm::to_lower(name);

    #ifdef __HAS_TFHE__
    if (name == "tfhe") return BooleanCircuitBackendType::TFHE;
    #endif

    return BooleanCircuitBackendType::UNKNOWN;
  } 

  //
  // BooleanCircuitBackendFactoryException class implementation
  //

  BooleanCircuitBackendFactoryException::BooleanCircuitBackendFactoryException(const char* msg) 
  {
    this->msg = msg;
  }

  const char* BooleanCircuitBackendFactoryException::getMessage() {
    return this->msg;
  }  
}