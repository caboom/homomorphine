#include "constants.hpp"

namespace homomorphine
{
  // SEAL default values
  const int Constants::SEAL_POLY_MODULUS_DEGREE = 4096;
  const uint64_t Constants::SEAL_COEFF_MODULUS = 4096;
  const int Constants::SEAL_PLAIN_MODULUS = 40961;
  const double Constants::SEAL_CKKS_SCALE = pow(2.0, 60);
  const int Constants::SEAL_SECURITY_LEVEL = 128;

  // HELib default values
  const unsigned long Constants::HELIB_PLAINTEXT_PRIME_MODULUS = 1021;
  const unsigned long Constants::HELIB_HENSEL_LIFTING = 1;
  const unsigned long Constants::HELIB_MODULUS_CHAIN_BITS = 16;
  const unsigned long Constants::HELIB_NUMBER_OF_COLUMNS = 3;
  const unsigned long Constants::HELIB_HAMMING_WEIGHT = 64;
  const unsigned long Constants::HELIB_SECURITY_LEVEL = 128;
  const unsigned long Constants::HELIB_DEGREE_OF_FIELD_EXTENSION = 0;
}