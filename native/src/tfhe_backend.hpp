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
      TFheGateBootstrappingSecretKeySet* secret_key = nullptr;       /*!< secret key (contains public/cloud key as well) */
      const TFheGateBootstrappingCloudKeySet* public_key = nullptr;  /*!< public key */

      /*!
       * Generate seed vector
       * 
       * /param size vector size
       * /return seed vector
       * 
       */
      vector<uint32_t> getSeed(int &size);

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
       * Returns the UUEncoded secret key
       * 
       * \return secret key
       */
      string getSecretKey();

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
       * Sets the secret key 
       * 
       * \param secret_key UUEncoded secret key
       */
      void setSecretKey(string secret_key);

      /*!
       * Sets the both public and secret keys 
       * 
       * \param public_key UUEncoded public key
       * \param secret_key UUEncoded secret key
       */
      void setKeys(string public_key, string secret_key);

      /*!
       * Returns the UUEncoded cipher containing ecrypted value, or vector of values
       * 
       * \return UUEncoded cipher
       */
      string getCipher();

      /*!
       * Sets the UUEncoded cipher containing ecrypted value, or vector of values
       * 
       * \param cipher UUEncoded cipher
       */
      void setCipher(string cipher);

      /*!
       * Perform boolean operation on cypher
       * 
       * \param value value
       * \param operation type of operation
       */
      void process(int value, BooleanCircuitOperation operation);
  };
}

#endif