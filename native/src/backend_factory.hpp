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
  //! Type of Homomorphic Backend (Currently supported: SEAL, HELib)
  enum BackendType { 
    B_SEAL,    /*!< SEAL Backend */
    B_HELib,   /*!< HELib Backend */
    B_UNKNOWN  /*!< Unknown backend - usually represents an error in resolving the backend */
  }; 

  /**! /brief Factory for generating specific homomorphic backend.
   *  
   * BackendFactory is generating a specific homomorphic backend 
   * and interface that each backend need to provide is defined by 
   * Backend class.  
   */
  class BackendFactory
  {
    public:
      
      /**!
       * Create a backend using the name of the backend.
       * 
       * \param name string literal with name of the backend
       * \return specific implementation of Backend interface
       */
      static Backend* create(string name);

      /**!
       * Create a backend using the backend type.
       * 
       * \param type backend type
       * \return specific implementation of Backend interface
       */
      static Backend* create(BackendType type);

      /**!
       * Resolves the type of the backend using the name of the backend.
       * 
       * \param name string literal with name of the backend
       * \return backend type
       */
      static BackendType getType(string name);
  };

  /**! /brief BackendFactory exception.
   * 
   * Thrown in case BackendFactory can't provide, or resolve a
   * specific backend.
   */
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