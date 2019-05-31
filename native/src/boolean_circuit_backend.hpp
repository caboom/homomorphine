#ifndef _BOOLEAN_CIRCUIT_HOMOMORPHINE_BACKEND_H_
#define _BOOLEAN_CIRCUIT_HOMOMORPHINE_BACKEND_H_

#include <string>
#include <vector>
#include <iostream>

#include "backend.hpp"

using namespace std;

namespace homomorphine 
{
  /*! /brief Backend interface
   * 
   * Provides an interface that each specific boolean circuit backend has to provide
   */
  class BooleanCircuitBackend : public Backend
  {
    protected:
      map<string, string> params; /*!< params that are consumed by specific implementations of the boolean circuit homomorphic backend */

    public:

      /*! 
       * Backend cleanup
       */
      virtual ~BooleanCircuitBackend() { this->params.clear(); };

      /*! 
       * Sets the specific homomorphic algorithm implementation
       * that boolean circuit backend provides
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
  };

}

#endif