#ifndef _HOMOMORPHINE_BACKEND_H_
#define _HOMOMORPHINE_BACKEND_H_

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <utility>
#include <exception>

using namespace std;

namespace homomorphine 
{
  /*! /brief Backend interface
   * 
   * Provides an interface that each specific arithmetic backend has to provide
   */
  class Backend
  {
    private:
      map<string, string> params; /*!< params that are consumed by specific implementations of the arithmetic homomorphic backend */

    public:
      /*!
       * Returns the map of the params that have been set
       * 
       * \return map of params
       */
      map<string, string> getParams();

      /*!
       * Sets the map of the params
       * 
       * \param params map of params
       */
      void setParams(map<string, string> &params); 

      /*!
       * Returns the specific parameter
       * 
       * \param key parameter name
       * \return parameter value
       */
      string getParam(string key);

      /*!
       * Sets the specific parameter
       * 
       * \param key parameter name
       * \param value parameter value
       */
      void  setParam(string &key, string &value);
  };

  /*! /brief Backend exception.
   * 
   * Thrown in case of a fatal error of specific backend
   * implementation.
   */
  class BackendException : public std::exception 
  {
	  private:
      const char* msg; /*!< exception message */

    public:
      BackendException(const char* msg);

      const char* getMessage();
  };

  /*! /brief Backend operation exception.
   * 
   * Thrown in case specific Backend can't provide, or resolve a
   * specific operation (i.e. not all arithmetic operations are 
   * provided by each backend).
   */
  class BackendOperationNotSupported : public std::exception 
  {
	  private:
      const char* msg; /*!< exception message */

    public:
      BackendOperationNotSupported(const char* msg);

      const char* getMessage();
  };
}

#endif