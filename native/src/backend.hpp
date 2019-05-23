#ifndef _HOMOMORPHINE_BACKEND_H_
#define _HOMOMORPHINE_BACKEND_H_

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <utility>
#include <exception>
#include <boost/algorithm/string.hpp>

using namespace std;

namespace homomorphine 
{
  
  /*! /brief Backend interface
   * 
   * Provides an interface that each specific backend has to provide
   */
  class Backend
  {
    protected:
      map<string, string> params; /*!< params that are consumed by specific implementations of the homomorphic backend */

    public:

      /*! 
       * Backend cleanup
       */
      virtual ~Backend() {}

      /*! 
       * Sets the specific homomorphic algorithm implementation
       * that backend provides
       * 
       * \param algorithm homomorphic encryption algorithm
       */
      virtual void setAlgorithm(string algorithm) = 0;

      /*!
       * Backend initialization method - initializes all the basic
       * parameters and behavior of a specific backend implementation
       */
      virtual void init() = 0;

      /*!
       * Generates the public/secret key pair
       */
      virtual void generateKeys() = 0;

      /*!
       * Returns the UUEncoded public key
       * 
       * \return public key
       */
      virtual string getPublicKey() = 0;

      /*!
       * Returns the UUEncoded secret key
       * 
       * \return secret key
       */
      virtual string getSecretKey() = 0;

      /*!
       * Returns the pair of UUEncoded public and secret keys
       * 
       * \return pair of public and secret keys
       */
      virtual pair<string, string> getKeys() = 0; 

      /*!
       * Sets the public key 
       * 
       * \param public_key UUEncoded public key
       */
      virtual void setPublicKey(string public_key) = 0;

      /*!
       * Sets the secret key 
       * 
       * \param secret_key UUEncoded secret key
       */
      virtual void setSecretKey(string secret_key) = 0;

      /*!
       * Sets the both public and secret keys 
       * 
       * \param public_key UUEncoded public key
       * \param secret_key UUEncoded secret key
       */
      virtual void setKeys(string public_key, string secret_key) = 0;

      /*!
       * Returns the UUEncoded cipher containing ecrypted value, or vector of values
       * 
       * \return UUEncoded cipher
       */
      virtual string getCipher() = 0;

      /*!
       * Sets the UUEncoded cipher containing ecrypted value, or vector of values
       * 
       * \param cipher UUEncoded cipher
       */
      virtual void setCipher(string cipher) = 0;

      /*!
       * Encrypts the vector of values using the public key
       * 
       * \param values vector of values
       * \return UUEncoded cipher
       */
      virtual string encrypt(vector<long> values) = 0; 

      /*!
       * Encrypts the single value using the public key
       * 
       * \param value value
       * \return UUEncoded cipher
       */
      virtual string encrypt(long value) = 0;

      /*!
       * Decrypts the vector of values using the secret key
       * 
       * \return vector of decrypted values
       */
      virtual vector<long> decryptValues() = 0;

      /*!
       * Decrypts the single value using the secret key
       * 
       * \return decrypted value
       */
      virtual long decrypt() = 0;

      /*!
       * Adds the vector of values to encrypted vector of values
       * 
       * \param values vector of values
       */
      virtual void add(vector<long> values) = 0;

      /*!
       * Adds the value to encrypted value
       * 
       * \param value value
       */
      virtual void add(long value) = 0;

      /*!
       * Negates a single encrypted value, or a vector of encrypted values
       */
      virtual void negate() = 0;

      /*!
       * Multiplies the vector of values with the encrypted vector of values
       * 
       * \param values vector of values
       */
      virtual void multiply(vector<long> values) = 0;

      /*!
       * Multiplies the value with the encrypted value
       * 
       * \param value value
       */
      virtual void multiply(long value) = 0;

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