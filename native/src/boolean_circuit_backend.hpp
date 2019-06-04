#ifndef _BOOLEAN_CIRCUIT_HOMOMORPHINE_BACKEND_H_
#define _BOOLEAN_CIRCUIT_HOMOMORPHINE_BACKEND_H_

#include <string>
#include <vector>
#include <iostream>

#include "backend.hpp"

using namespace std;

namespace homomorphine 
{
  /*! 
   * Types of boolean circuit operations
   */
  enum class BooleanCircuitOperation { 
    NOT,    /*!< Boolean NOT operation */
    COPY,   /*!< Boolean COPY operation */
    NAND,   /*!< Boolean NAND operation */
    OR,     /*!< Boolean OR operation */
    AND,    /*!< Boolean AND operation */
    XOR,    /*!< Boolean XOR operation */
    XNOR,   /*!< Boolean XNOR operation */
    NOR,    /*!< Boolean NOR operation */
    ANDNY,  /*!< Boolean ADDNY operation */ 
    ANDYN,  /*!< Boolean ADDYN operation */
    ORNY,   /*!< Boolean ORNY operation */
    ORYN,   /*!< Boolean ORYN operation */
    MUX     /*!< Boolean MUX operation */
  }; 

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
       * Writes the public key to a stream
       * 
       * \param stream public key stream
       */
      virtual void writePublicKeyToStream(ostream& stream) = 0;

      /*!
       * Returns the UUEncoded secret key
       * 
       * \return secret key
       */
      virtual string getSecretKey() = 0;

      /*!
       * Writes the secret key to a stream
       * 
       * \param stream secret key stream
       */
      virtual void writeSecretKeyToStream(ostream& stream) = 0;

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
       * Sets the public key from stream
       * 
       * \param stream public key binary stream
       */
      virtual void readPublicKeyFromStream(istream &stream) = 0;

      /*!
       * Sets the secret key 
       * 
       * \param secret_key UUEncoded secret key
       */
      virtual void setSecretKey(string secret_key) = 0;

      /*!
       * Sets the secret key from stream
       * 
       * \param stream secret key binary stream
       */
      virtual void readSecretKeyFromStream(istream &stream) = 0;

      /*!
       * Sets the both public and secret keys 
       * 
       * \param public_key UUEncoded public key
       * \param secret_key UUEncoded secret key
       */
      virtual void setKeys(string public_key, string secret_key) = 0;

      /*!
       * Encrypts the single value using the secret key
       * 
       * \param value integer value that will be encrypted
       * \return UUEncoded cipher
       */
      virtual string encryptToString(int value) = 0;

      /*!
       * Encrypts the single value using the secret key and writes it to output stream
       * 
       * \param value integer value that will be be encrypted
       * \param stream output stream
       */
      virtual void encryptToStream(int value, ostream& stream) = 0;
      
      /*!
       * Encodes the single value using the public key (use instead encryption on public end)
       * 
       * \param value integer value that will be encoded
       * \return UUEncoded cipher
       */
      virtual string encodeToString(int value) = 0;

      /*!
       * Encodes the single value using the public key and writes it to output stream (use instead encryption on public end)
       * 
       * \param value integer value that will be be encoded
       * \param stream output stream
       */
      virtual void encodeToStream(int value, ostream& stream) = 0;

      /*!
       * Decrypts the single value using the secret key
       * 
       * \return decrypted value
       */
      virtual int decryptFromStream(istream& stream) = 0;

      /*!
       * Perform boolean operation on single cipher
       * 
       * \param cipher_x cipher #1
       * \param operation type of operation
       */
      virtual void process(ostream& result, istream& cipher_x, BooleanCircuitOperation operation) = 0;

      /*!
       * Perform boolean operation on 2 ciphers
       * 
       * \param cipher_x cipher #1
       * \param cipher_y cipher #2
       * \param operation type of operation
       */
      virtual void process(ostream& result, istream& cipher_x, istream& cipher_y, BooleanCircuitOperation operation) = 0;

      /*!
       * Perform boolean operation on 3 ciphers
       * 
       * \param cipher_x cipher #1
       * \param cipher_y cipher #2
       * \param cipher_y cipher #3
       * \param operation type of operation
       */
      virtual void process(ostream& result, istream& cipher_x, istream& cipher_y, istream& cipher_z, BooleanCircuitOperation operation) = 0;
  };

}

#endif