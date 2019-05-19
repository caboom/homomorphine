#ifndef _HOMOMORPHINE_BACKEND_FACTORY_H_
#define _HOMOMORPHINE_BACKEND_FACTORY_H_

#include <string>
#include <boost/algorithm/string.hpp>

#include "backend.hpp"
#include "seal_backend.hpp"
#include "helib_backend.hpp"

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