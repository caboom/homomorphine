#ifndef _HOMOMORPHINE_SEAL_BACKED_H_
#define _HOMOMORPHINE_SEAL_BACKED_H_

#include <iostream>
#include <utility>
#include <sstream>
#include <string>
#include <seal/seal.h>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>

#include "util.hpp"
#include "backend.hpp"
#include "constants.hpp"

using namespace seal;
using namespace std;
using namespace boost::archive::iterators;

namespace homomorphine 
{
  enum SealAlgorithmType { 
    SEAL_BFV, SEAL_CKKS, SEAL_UNKNOWN
  }; 

  class SealBackend : public Backend
  {
    private:
      std::shared_ptr<SEALContext> context;
      IntegerEncoder *encoder;
      KeyGenerator *keygen;
      SealAlgorithmType type;
      EncryptionParameters *encryption_params;
      PublicKey public_key;
      SecretKey secret_key;
      Ciphertext cipher;

      SealAlgorithmType getAlgorithmType(string name);
      void initBFV();  

    public:
      ~SealBackend();
      void init();
      void setAlgorithm(string algorithm);
      void setAlgorithm(SealAlgorithmType algorithm);
      string generateEncodedPublicKey();
      string generateEncodedSecretKey();
      pair<string, string> generateEncodedKeys();

      PublicKey getPublicKey();
      SecretKey getSecretKey();
      pair<PublicKey, SecretKey> getKeys();
      void setValue(int value);
      void setPublicKey(PublicKey public_key);
      void setSecretKey(SecretKey secret_key);
      void setKeys(PublicKey public_key, SecretKey secret_key);
      void setPublicKey(string public_key);
      void setSecretKey(string secret_key);
      void setKeys(string public_key, string secret_key);
      string getEncodedCipher();
      void setEncodedCipher(string encoded_cipher);
      PublicKey generatePublicKey();
      SecretKey generateSecretKey();
      pair<PublicKey, SecretKey> generateKeys();
      string encryptValue(int value);
      int decrypt();
      void add(int value);
      void negate();
      void multiply(int value);
  };
}

#endif