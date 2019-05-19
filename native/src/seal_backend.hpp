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
      SealAlgorithmType algorithm;
      EncryptionParameters *encryption_params;
      PublicKey public_key;
      SecretKey secret_key;
      Ciphertext cipher;
      double scale;

      SealAlgorithmType getAlgorithmType(string name);
      void initBFV();  
      void initCKKS();  
      Plaintext encodeWithBFV(vector<int64_t> values);
      Plaintext encodeWithCKKS(vector<int64_t> values);

    public:
      ~SealBackend();
      void init();
      void setAlgorithm(string algorithm);
      void setAlgorithm(SealAlgorithmType algorithm);
      void generateKeys();
      string getPublicKey();
      string getSecretKey();
      pair<string, string> getKeys();
      void setPublicKey(string public_key);
      void setSecretKey(string secret_key);
      void setKeys(string public_key, string secret_key);
      string getCipher();
      void setCipher(string cipher);
      string encrypt(vector<int64_t> values);
      string encrypt(int64_t value);
      vector<int64_t> decryptValues();
      int64_t decrypt();
      void add(vector<int64_t> values);
      void add(int64_t value);
      void negate();
      void multiply(vector<int64_t> values);
      void multiply(int64_t value);

      // SEAL specific interface
      PublicKey getSealPublicKey();
      SecretKey getSealSecretKey();
      pair<PublicKey, SecretKey> getSealKeys();
      void setSealPublicKey(PublicKey public_key);
      void setSealSecretKey(SecretKey secret_key);
      void setSealKeys(PublicKey public_key, SecretKey secret_key);
  };
}

#endif