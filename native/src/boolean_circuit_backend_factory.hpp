#ifndef _HOMOMORPHINE_BOOLEAN_CIRCUIT_BACKEND_FACTORY_H_
#define _HOMOMORPHINE_BOOLEAN_CIRCUIT_BACKEND_FACTORY_H_

#include <string>
#include <boost/algorithm/string.hpp>

#include "info.hpp"
#include "boolean_circuit_backend.hpp"

#ifdef __HAS_TFHE__
#include "tfhe_backend.hpp"
#endif

using namespace std;

namespace homomorphine 
{
  //! Type of Boolean Circuit Homomorphic Backend (Currently supported: TFHE)
  enum class BooleanCircuitBackendType { 
    TFHE,    /*!< TFHE Backend */
    UNKNOWN  /*!< Unknown backend - usually represents an error in resolving the backend */
  }; 

  /*! /brief Factory for generating specific boolean circuit homomorphic backend.
   *  
   * BooleanCircuitBackendFactory is generating a specific boolean circuit
   * backend and interface that each backend need to provide is defined by 
   * BooleanCircuitBackend class.  
   */
  class BooleanCircuitBackendFactory
  {
    public:
      
      /*!
       * Create a backend using the name of the backend.
       * 
       * \param name string literal with name of the backend
       * \return specific implementation of Backend interface
       */
      static BooleanCircuitBackend* create(string name);

      /*!
       * Create a boolean circuit backend using the backend type.
       * 
       * \param type backend type
       * \return specific implementation of Backend interface
       */
      static BooleanCircuitBackend* create(BooleanCircuitBackendType type);

      /*!
       * Resolves the type of the boolean circuit backend using the name of the backend.
       * 
       * \param name string literal with name of the backend
       * \return backend type
       */
      static BooleanCircuitBackendType getType(string name);
  };

  /*! /brief BooleanCircuitBackendFactory exception.
   * 
   * Thrown in case BooleanCircuitBackendFactory can't provide, or resolve a
   * specific backend.
   */
  class BooleanCircuitBackendFactoryException : public std::exception 
  {
	  private:
      const char* msg; /*!< exception message */

    public:
      BooleanCircuitBackendFactoryException(const char* msg);

      const char* getMessage();
  };
}

#endif