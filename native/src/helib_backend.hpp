#ifndef _HOMOMORPHINE_HELIB_BACKED_H_
#define _HOMOMORPHINE_HELIB_BACKED_H_

#include <iostream>
#include <utility>
#include <sstream>
#include <string>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>
#include <helib/FHE.h>
#include <helib/EncryptedArray.h>

#include "util.hpp"
#include "backend.hpp"
#include "constants.hpp"

using namespace NTL;
using namespace std;
using namespace boost::archive::iterators;

namespace homomorphine 
{
  //! HELib algorithms - there is only one used
  enum HELibAlgorithmType { 
    HELIB_DEFAULT_ALGORITHM
  }; 

  /*! /brief HELib backend
   *
   * This class is implementing HELib backend implementation
   */
  class HELibBackend : public Backend
  {
    private:
      FHEcontext* context = nullptr;   /*!< HELib context object */
      FHEPubKey* public_key = nullptr; /*!< HELib public key */
      FHESecKey* secret_key = nullptr; /*!< HELib secret */
      ZZX polynomial;                  /*!< NTL polynomial, used internally by HELib */
      Ctxt* cipher = nullptr;          /*!< cipher */
      HELibAlgorithmType algorithm;    /*!< HELib algorithm type */

      unsigned long hamming_weight;    /*!< Hamming weight - used for encrypting the value(s) */

    public:
       
      /*! 
       * HELib backend cleanup
       */
      ~HELibBackend();

      /*! 
       * Sets the specific HELib algorithm implementation
       * that backend provides (currently, only default one)
       * 
       * \param algorithm homomorphic encryption algorithm
       */
      void setAlgorithm(string algorithm);

      /*!
       * Initializes the HELib backend
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
       * Encrypts the vector of values using the public key
       * 
       * \param values vector of values
       * \return UUEncoded cipher
       */
      string encrypt(vector<long> values); 

      /*!
       * Encrypts the single value using the public key
       * 
       * \param value value
       * \return UUEncoded cipher
       */
      string encrypt(long value);

      /*!
       * Decrypts the vector of values using the secret key
       * 
       * \return vector of decrypted values
       */
      vector<long> decryptValues();

      /*!
       * Decrypts the single value using the secret key
       * 
       * \return decrypted value
       */
      long decrypt();

      /*!
       * Adds the vector of values to encrypted vector of values
       * 
       * \param values vector of values
       */
      void add(vector<long> values);

      /*!
       * Adds the value to encrypted value
       * 
       * \param value value
       */
      void add(long value);

      /*!
       * Negates a single encrypted value, or a vector of encrypted values
       */
      void negate();

      /*!
       * Multiplies the vector of values with the encrypted vector of values
       * 
       * \param values vector of values
       */
      void multiply(vector<long> values);

      /*!
       * Multiplies the value with the encrypted value
       * 
       * \param value value
       */
      void multiply(long value);
  };
}

#endif