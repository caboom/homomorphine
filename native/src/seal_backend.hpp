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
      Plaintext encodeWithBFV(vector<long> values);
      Plaintext encodeWithCKKS(vector<long> values);

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
      string encrypt(vector<long> values);
      string encrypt(long value);
      vector<long> decryptValues();
      long decrypt();
      void add(vector<long> values);
      void add(long value);
      void negate();
      void multiply(vector<long> values);
      void multiply(long value);

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