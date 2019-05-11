#include "constants.hpp"

namespace homomorphine
{
  const int Constants::SEAL_POLY_MODULUS_DEGREE = 4096;
  const uint64_t Constants::SEAL_COEFF_MODULUS = 4096;
  const int Constants::SEAL_PLAIN_MODULUS = 40961;
  const double Constants::SEAL_CKKS_SCALE = pow(2.0, 60);
  const int Constants::SECURITY_LEVEL = 128;
}