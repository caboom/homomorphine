#ifndef _HOMOMORPHINE_SEAL_BACKED_H_
#define _HOMOMORPHINE_SEAL_BACKED_H_

#include <iostream>
#include <utility>
#include <seal/seal.h>

using namespace seal;
using namespace std;

#include "backend.hpp"

namespace Homomorphine 
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

      PublicKey generatePublicKey();
      SecretKey generateSecretKey();
      pair <PublicKey, SecretKey> generatePublicAndSecretKey();
  };
}

#endif