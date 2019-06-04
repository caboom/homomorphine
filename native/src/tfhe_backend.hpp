#ifndef _HOMOMORPHINE_TFHE_BACKED_H_
#define _HOMOMORPHINE_TFHE_BACKED_H_

#include <iostream>
#include <utility>
#include <sstream>
#include <string>
#include <tfhe/tfhe.h>
#include <tfhe/tfhe_io.h>

#include "util.hpp"
#include "backend.hpp"
#include "boolean_circuit_backend.hpp"
#include "constants.hpp"

using namespace std;

namespace homomorphine 
{
  //! TFHE algorithms - there is only one used
  enum class TFHEAlgorithm { 
    DEFAULT
  }; 

  /*! /brief TFHE backend
   *
   * This class is an implementation of the SEAL backend.
   */
  class TFHEBackend : public BooleanCircuitBackend
  {
    private:
      TFHEAlgorithm algorithm;                                       /*!< TFHE algorithm type */
      TFheGateBootstrappingParameterSet *context = nullptr;          /*!< TFHE params */
      int random_depth;                                              /*!< random vector depth */
      int bits_encrypt;                                              /*!< number of bits used for encryption */
      TFheGateBootstrappingSecretKeySet* secret_key = nullptr;       /*!< secret key (contains public/cloud key as well) */
      const TFheGateBootstrappingCloudKeySet* public_key = nullptr;  /*!< public key */

      /*!
       * Generate seed vector
       * 
       * /param size vector size
       * /return seed vector
       */
      vector<uint32_t> getSeed(int &size);

      /*!
       * Reads TFHE cipher from a stream 
       * 
       * /param stream cipher stream
       * /return TFHE cipher
       */
      LweSample* readCipherFromStream(istream &stream); 

      /*!
       * Writes TFHE cipher to stream 
       * 
       * /param cipher TFHE cipher
       * /param stream cipher stream
       */
      void writeCipherToStream(LweSample* cipher, ostream& stream);

    public:
       
      /*! 
       * TFHE backend cleanup
       */
      ~TFHEBackend();

      /*! 
       * Sets the specific TFHE algorithm implementation
       * that backend provides (currently, only default one)
       * 
       * \param algorithm homomorphic encryption algorithm
       */
      void setAlgorithm(string algorithm);

      /*!
       * Initializes the TFHE backend
       */
      void init();

      /*!
       * Generates the public/secret key pair
       */
      void generateKeys();

      /*!
       * Returns the UUEncoded public key
       * 
       * \return public key
       */
      string getPublicKey();

      /*!
       * Writes the public key to a stream
       * 
       * \param stream public key stream
       */
      void writePublicKeyToStream(ostream& stream);

      /*!
       * Returns the UUEncoded secret key
       * 
       * \return secret key
       */
      string getSecretKey();

      /*!
       * Writes the secret key to a stream
       * 
       * \param stream secret key stream
       */
      void writeSecretKeyToStream(ostream& stream);

      /*!
       * Returns the pair of UUEncoded public and secret keys
       * 
       * \return pair of public and secret keys
       */
      pair<string, string> getKeys(); 

      /*!
       * Sets the public key 
       * 
       * \param public_key UUEncoded public key
       */
      void setPublicKey(string public_key);

      /*!
       * Sets the public key from stream
       * 
       * \param stream public key binary stream
       */
      void readPublicKeyFromStream(istream &stream);

      /*!
       * Sets the secret key 
       * 
       * \param secret_key UUEncoded secret key
       */
      void setSecretKey(string secret_key);

      /*!
       * Sets the secret key from stream
       * 
       * \param stream secret key binary stream
       */
      void readSecretKeyFromStream(istream &stream);

      /*!
       * Sets the both public and secret keys 
       * 
       * \param public_key UUEncoded public key
       * \param secret_key UUEncoded secret key
       */
      void setKeys(string public_key, string secret_key);

      /*!
       * Encrypts the single value using the public key and returns UUEncoded cyphertext
       * 
       * \param value integer value that will be be encrypted
       * \return UUEncoded cipher
       */
      string encryptToString(int value);

      /*!
       * Encrypts the single value using the secret key and writes it to output stream
       * 
       * \param value integer value that will be be encrypted
       * \param stream output stream
       */
      void encryptToStream(int value, ostream& stream);

      /*!
       * Decrypts the single value using the secret key
       * 
       * \return decrypted value
       */
      int decryptFromStream(istream& stream);

      /*!
       * Perform boolean operation on single cipher
       * 
       * \param cipher_x cipher #1
       * \param operation type of operation
       */
      void process(ostream& result, istream& cipher_x, BooleanCircuitOperation operation);


      /*!
       * Perform boolean operation on 2 ciphers
       * 
       * \param cipher_x cipher #1
       * \param cipher_y cipher #2
       * \param operation type of operation
       */
      void process(ostream& result, istream& cipher_x, istream& cipher_y, BooleanCircuitOperation operation);

      /*!
       * Perform boolean operation on 3 ciphers
       * 
       * \param cipher_x cipher #1
       * \param cipher_y cipher #2
       * \param cipher_y cipher #3
       * \param operation type of operation
       */
      void process(ostream& result, istream& cipher_x, istream& cipher_y, istream& cipher_z, BooleanCircuitOperation operation);
  };
}

#endif