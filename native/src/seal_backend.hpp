#ifndef _HOMOMORPHINE_SEAL_BACKED_H_
#define _HOMOMORPHINE_SEAL_BACKED_H_

#include <iostream>
#include <utility>
#include <sstream>
#include <string>
#include <math.h>
#include <seal/seal.h>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>

#include "util.hpp"
#include "backend.hpp"
#include "arithmetic_backend.hpp"
#include "constants.hpp"

using namespace seal;
using namespace std;
using namespace boost::archive::iterators;

namespace homomorphine 
{
  
  //! SEAL algorithms 
  enum class SealAlgorithm { 
    BFV,     /*!< SEAL BFV backend */
    CKKS,    /*!< SEAL CKKS backend */
    UNKNOWN  /*!< Unknown algorithm type - usually an error */
  }; 

  /*! /brief SEAL backend
   *
   * This class is an implementation of the SEAL backend.
   */
  class SealBackend : public ArithmeticBackend
  {
    private:
      std::shared_ptr<SEALContext> context;               /*!< SEAL context object */
      KeyGenerator *keygen = nullptr;                     /*!< SEAL key generator */
      SealAlgorithm algorithm;                            /*!< SEAL algorithm type (BFV, or CKKS) */
      EncryptionParameters *encryption_params = nullptr;  /*!< SEAL specific encryption parameters */
      PublicKey public_key;                               /*!< SEAL public key */
      SecretKey secret_key;                               /*!< SEAL secret key */
      RelinKeys relin_keys;                               /*!< SEAL relinearization keys */
      Ciphertext cipher;                                  /*!< cipher */
      double scale;                                       /*!< bit-precision of encoding, used by CKKS encryption implementation */

      /*!
       * Get SEAL algorithm type from algorithm name
       * 
       * \param name algorithm name
       * \return algorithm type
       */
      SealAlgorithm getAlgorithmType(string name);

      /*!
       * Initialize BFV specific stuff of SEAL backend
       */
      void initBFV();  

      /*!
       * Initialize CKKS specific stuff of SEAL backend
       */
      void initCKKS();  

      /*!
       * Encode vector of values using BFV algorithm
       * 
       * \param values vector of values
       * \return plaintext representation of values
       */
      Plaintext encodeWithBFV(vector<long> values);

      /*!
       * Encode single value using BFV algorithm
       * 
       * \param value value
       * \return plaintext representation of value
       */
      Plaintext encodeWithBFV(long value);

      /*!
       * Encode vector of values using CKKS algorithm
       * 
       * \param values vector of values
       * \return plaintext representation of values
       */
      Plaintext encodeWithCKKS(vector<long> values);

      /*!
       * Encode single value using CKKS algorithm
       * 
       * \param value value
       * \return plaintext representation of value
       */
      Plaintext encodeWithCKKS(long value);

      /*!
       * Decode value from plaintext using BFV algorithm
       * 
       * \param plain_result plaintext representation of value
       * \return value
       */
      long decodeWithBFV(Plaintext plain_result);

      /*!
       * Decode vector of values from plaintext using BFV algorithm
       * 
       * \param plain_result plaintext representation of value
       * \return value
       */
      vector<long> decodeValuesWithBFV(Plaintext plain_result);

      /*!
       * Decode value from plaintext using CKKS algorithm
       * 
       * \param plain_result plaintext representation of value
       * \return vector of values
       */
      long decodeWithCKKS(Plaintext plain_result);

      /*!
       * Decode vector of value from plaintext using CKKS algorithm
       * 
       * \param plain_result plaintext representation of value
       * \return vector of values
       */
      vector<long> decodeValuesWithCKKS(Plaintext plain_result);

    public:

      /*! 
       * SEAL backend cleanup
       */
      ~SealBackend();

      /*!
       * Initializes the SEAL backend
       */
      void init();

      /*! 
       * Sets the specific SEAL algorithm implementation
       * that backend provides (currently, BFV and CKKS)
       * 
       * \param algorithm homomorphic encryption algorithm
       */
      void setAlgorithm(string algorithm);

      /*! 
       * Sets the specific SEAL algorithm implementation
       * that backend provides using the name of algorithm
       * 
       * \param algorithm homomorphic encryption algorithm
       */
      void setAlgorithm(SealAlgorithm algorithm);

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
       * Returns the UUEncoded cipher containing ecrypted value, or vector of values
       * 
       * \return UUEncoded cipher
       */
      string getCipher();

      /*!
       * Writes the cipher to output stream
       * 
       * \param stream output stream
       */
      void writeCipherToStream(ostream& stream);

      /*!
       * Sets the UUEncoded cipher containing ecrypted value, or vector of values
       * 
       * \param cipher UUEncoded cipher
       */
      void setCipher(string cipher);

      /*!
       * Reads the cipher from input stream
       * 
       * \param stream cipher stream
       */
      void readCipherFromStream(istream &stream);

      /*!
       * Encrypts the vector of values using the public key
       * 
       * \param values vector of values
       * \return UUEncoded cipher
       */
      void encrypt(vector<long> values);

      /*!
       * Encrypts the single value using the public key
       * 
       * \param value value
       * \return UUEncoded cipher
       */
      void encrypt(long value);

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