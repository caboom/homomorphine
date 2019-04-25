#include "backend_factory.hpp"

namespace Homomorphine 
{
  Backend* BackendFactory::create(BackendType type)
  {
    return new SealBackend();
  }
  
  BackendType BackendFactory::getType(string name) {
    boost::algorithm::to_lower(name);

    if (name == "seal") return B_SEAL;
    if (name == "helib") return B_HELib;

    return B_UNKNOWN;
  } 
}