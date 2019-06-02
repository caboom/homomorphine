#ifndef _HOMOMORPHINE_ARITHMETIC_BACKEND_FACTORY_H_
#define _HOMOMORPHINE_ARITHMETIC_BACKEND_FACTORY_H_

#include <string>
#include <boost/algorithm/string.hpp>

#include "info.hpp"
#include "util.hpp"
#include "arithmetic_backend.hpp"

#ifdef __HAS_SEAL__
#include "seal_backend.hpp"
#endif

#ifdef __HAS_HELIB__
#include "helib_backend.hpp"
#endif

using namespace std;

namespace homomorphine 
{
  //! Type of Homomorphic Backend (Currently supported: SEAL, HELib)
  enum class ArithmeticBackendType { 
    SEAL,    /*!< SEAL Backend */
    HELIB,   /*!< HELib Backend */
    UNKNOWN  /*!< Unknown backend - usually represents an error in resolving the backend */
  }; 

  /*! /brief Factory for generating specific homomorphic backend.
   *  
   * ArithmeticBackendFactory is generating a specific arithmetic homomorphic 
   * backend and interface that each backend need to provide is defined by 
   * ArithmeticBackend class.  
   */
  class ArithmeticBackendFactory
  {
    public:
      
      /*!
       * Create an arithmetic backend using the name of the backend.
       * 
       * \param name string literal with name of the backend
       * \return specific implementation of Backend interface
       */
      static ArithmeticBackend* create(string name);

      /*!
       * Create an arithmetic backend using the backend type.
       * 
       * \param type backend type
       * \return specific implementation of Backend interface
       */
      static ArithmeticBackend* create(ArithmeticBackendType type);

      /*!
       * Resolves the type of the arithmetic backend using the name of the backend.
       * 
       * \param name string literal with name of the backend
       * \return backend type
       */
      static ArithmeticBackendType getType(string name);
  };

  /*! /brief ArithmeticBackendFactory exception.
   * 
   * Thrown in case ArithmeticBackendFactory can't provide, or resolve a
   * specific backend.
   */
  class ArithmeticBackendFactoryException : public std::exception 
  {
	  private:
      const char* msg; /*!< exception message */

    public:
      ArithmeticBackendFactoryException(const char* msg);

      const char* getMessage();
  };
}

#endif