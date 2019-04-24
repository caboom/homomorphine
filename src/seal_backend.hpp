#include <iostream>
#include <seal/seal.h>

using namespace seal;
using namespace std;

#ifndef _MORPHINE_SEAL_BACKED_H_
#define _MORPHINE_SEAL_BACKED_H_

#include "backend.hpp"

namespace Morphine 
{
  enum SealAlgorithmType { 
    SEAL_BFV, SEAL_CKKS, SEAL_UNKNOWN
  }; 


  class SealBackend : public Backend
  {
    private:
      SealAlgorithmType type;
      EncryptionParameters *encryption_params;

      SealAlgorithmType getAlgorithmType(string name);
      void initBFV();

    public:
      ~SealBackend();
      void init();
      void setAlgorithm(string algorithm);
  };
}

#endif