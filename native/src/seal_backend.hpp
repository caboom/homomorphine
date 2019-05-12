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
      BatchEncoder *encoder;
      KeyGenerator *keygen;
      SealAlgorithmType type;
      EncryptionParameters *encryption_params;
      PublicKey public_key;
      SecretKey secret_key;
      Ciphertext cipher;
      double scale;

      SealAlgorithmType getAlgorithmType(string name);
      void initBFV();  
      void initCKKS();  
      Plaintext encodeWithBFV(vector<uint64_t> values);
      Plaintext encodeWithCKKS(vector<uint64_t> values);


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
      string encrypt(vector<uint64_t> values);
      string encrypt(int value);
      vector<uint64_t> decryptValues();
      int decrypt();
      void add(vector<uint64_t> values);
      void add(int value);
      void negate();
      void multiply(vector<uint64_t> values);
      void multiply(int value);
  };
}

#endif