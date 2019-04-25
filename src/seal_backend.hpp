#ifndef _HOMOMORPHINE_SEAL_BACKED_H_
#define _HOMOMORPHINE_SEAL_BACKED_H_

#include <iostream>
#include <utility>
#include <seal/seal.h>
#include <boost/archive/iterators/base64_from_binary.hpp>

#include "backend.hpp"
#include "constants.hpp"

using namespace seal;
using namespace std;

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

      SealAlgorithmType getAlgorithmType(string name);
      void initBFV();

    public:
      ~SealBackend();
      void init();
      void setAlgorithm(string algorithm);
      void setAlgorithm(SealAlgorithmType algorithm);

      PublicKey generatePublicKey();
      SecretKey generateSecretKey();
      pair <PublicKey, SecretKey> generatePublicAndSecretKey();
      string getEncodedPublicKey();
      string getEncodedSecretKey();
      pair <string, string> getEncodedKeys();
  };
}

#endif