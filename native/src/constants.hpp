#ifndef _HOMOMORPHINE_CONSTANTS_H_
#define _HOMOMORPHINE_CONSTANTS_H_

#include <math.h>
#include <stdint.h>
#include <stddef.h>

namespace homomorphine 
{
  class Constants {
    public:
      static const int SEAL_POLY_MODULUS_DEGREE;
      static const uint64_t SEAL_COEFF_MODULUS;
      static const int SEAL_PLAIN_MODULUS;
      static const double SEAL_CKKS_SCALE;
      static const int SEAL_SECURITY_LEVEL;
      
      static const unsigned long HELIB_PLAINTEXT_PRIME_MODULUS;
      static const unsigned long HELIB_CYCLOTOMIC_POLYNOMIAL;
      static const unsigned long HELIB_HENSEL_LIFTING;
      static const unsigned long HELIB_MODULUS_CHAIN_BITS;
      static const unsigned long HELIB_NUMBER_OF_COLUMNS;
  };
}

#endif