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

      void process(ostream& result, istream& cipher_x, BooleanCircuitOperation operation);

      void process(ostream& result, istream& cipher_x, istream& cipher_y, BooleanCircuitOperation operation);

      void process(ostream& result, istream& cipher_x, istream& cipher_y, istream& cipher_z, BooleanCircuitOperation operation);

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
       * Encodes the single value using the public key (use instead encryption on public end)
       * 
       * \param value integer value that will be encoded
       * \return UUEncoded cipher
       */
      string encodeToString(int value);

      /*!
       * Encodes the single value using the public key and writes it to output stream 
       * (use instead encryption on public end)
       * 
       * \param value integer value that will be be encoded
       * \param stream output stream
       */
      void encodeToStream(int value, ostream& stream);

      /*!
       * Decrypts the single value using the secret key
       * 
       * \return decrypted value
       */
      int decryptFromStream(istream& stream);

      /*!
       * Perform boolean NOT operation on cipher
       * 
       * /param result stream with the result cipher
       * /param cipher cipher with encrypted value
       */
      void NOT(ostream& result, istream& cipher);

      /*!
       * Perform COPY operation on cipher (duplicate to other cipher stream)
       * 
       * /param cipher cipher with encrypted value
       */
      void COPY(ostream& result, istream& cipher);

      /*!
       * Perform boolean NAND operation on two ciphers
       * 
       * /param stream with the result cipher
       * /param cipher_x first cipher with encrypted value
       * /param cipher_y second cipher with encrypted value
       */
      void NAND(ostream& result, istream& cipher_x, istream& cipher_y);

      /*!
       * Perform boolean OR operation on two ciphers
       * 
       * /param stream with the result cipher
       * /param cipher_x first cipher with encrypted value
       * /param cipher_y second cipher with encrypted value
       */
      void OR(ostream& result, istream& cipher_x, istream& cipher_y);
      
      /*!
       * Perform boolean AND operation on two ciphers
       * 
       * /param stream with the result cipher
       * /param cipher_x first cipher with encrypted value
       * /param cipher_y second cipher with encrypted value
       */
      void AND(ostream& result, istream& cipher_x, istream& cipher_y);

      /*!
       * Perform boolean XOR operation on two ciphers
       * 
       * /param stream with the result cipher
       * /param cipher_x first cipher with encrypted value
       * /param cipher_y second cipher with encrypted value
       */
      void XOR(ostream& result, istream& cipher_x, istream& cipher_y);

      /*!
       * Perform boolean XNOR operation on two ciphers
       * 
       * /param stream with the result cipher
       * /param cipher_x first cipher with encrypted value
       * /param cipher_y second cipher with encrypted value
       */
      void XNOR(ostream& result, istream& cipher_x, istream& cipher_y);

      /*!
       * Perform boolean NOR operation on two ciphers
       * 
       * /param stream with the result cipher
       * /param cipher_x first cipher with encrypted value
       * /param cipher_y second cipher with encrypted value
       */
      void NOR(ostream& result, istream& cipher_x, istream& cipher_y);

      /*!
       * Perform boolean MUX operation on three ciphers (x ? y : z)
       * 
       * /param stream with the result cipher
       * /param cipher_x first cipher with encrypted value
       * /param cipher_y second cipher with encrypted value
       * /param cipher_z third cipher with encrypted value 
       */
      void MUX(ostream& result, istream& cipher_x, istream& cipher_y, istream& cipher_z);
  };
}

#endif