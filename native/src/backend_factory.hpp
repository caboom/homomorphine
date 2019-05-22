#ifndef _HOMOMORPHINE_BACKEND_FACTORY_H_
#define _HOMOMORPHINE_BACKEND_FACTORY_H_

#include <string>
#include <boost/algorithm/string.hpp>

#include "info.hpp"
#include "backend.hpp"

#ifdef __HAS_SEAL__
#include "seal_backend.hpp"
#endif

#ifdef __HAS_HELIB__
#include "helib_backend.hpp"
#endif

using namespace std;

namespace homomorphine 
{
  enum BackendType { 
    B_SEAL, B_HELib, B_UNKNOWN
  }; 

  class BackendFactory
  {
    public:
      static Backend* create(string type);
      static Backend* create(BackendType type);
      static BackendType getType(string name);
  };

  class BackendFactoryException : public std::exception 
  {
	  private:
      const char* msg;

    public:
      BackendFactoryException(const char* msg);

      const char* getMessage();
  };
}

#endif