#ifndef _HOMOMORPHINE_CONSTANTS_H_
#define _HOMOMORPHINE_CONSTANTS_H_

#include <math.h>

namespace homomorphine 
{
  class Constants {
    public:
      static const int SEAL_POLY_MODULUS_DEGREE;
      static const int SEAL_COEFF_MODULUS;
      static const double SEAL_CKKS_SCALE;
      static const int SECURITY_LEVEL;
  };
}

#endif