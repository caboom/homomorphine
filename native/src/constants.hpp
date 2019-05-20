#ifndef _HOMOMORPHINE_CONSTANTS_H_
#define _HOMOMORPHINE_CONSTANTS_H_

#include <math.h>
#include <stdint.h>
#include <stddef.h>

namespace homomorphine 
{
  class Constants {
    public:
      static const int SEAL_POLY_MODULUS_DEGREE = 4096;
      static const uint64_t SEAL_COEFF_MODULUS = 4096;
      static const int SEAL_PLAIN_MODULUS = 40961;
      static constexpr double SEAL_CKKS_SCALE = 1152921504606846976.0; // 2.0 ^ 60
      static const int SEAL_SECURITY_LEVEL = 128;
      
      static const unsigned long HELIB_PLAINTEXT_PRIME_MODULUS = 1021;
      static const unsigned long HELIB_HENSEL_LIFTING = 1;
      static const unsigned long HELIB_MODULUS_CHAIN_BITS = 16;
      static const unsigned long HELIB_NUMBER_OF_COLUMNS = 3;
      static const unsigned long HELIB_HAMMING_WEIGHT = 64;
      static const unsigned long HELIB_SECURITY_LEVEL = 128;
      static const unsigned long HELIB_DEGREE_OF_FIELD_EXTENSION = 0;
      static const unsigned long HELIB_MINIMUM_NUMBER_OF_SLOTS = 0;
  };
}

#endif