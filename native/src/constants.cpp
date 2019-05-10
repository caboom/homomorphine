#include "constants.hpp"

namespace homomorphine
{
  const int Constants::SEAL_POLY_MODULUS_DEGREE = 2048;
  const int Constants::SEAL_COEFF_MODULUS = 2048;
  const double Constants::SEAL_CKKS_SCALE = pow(2.0, 60);
  const int Constants::SECURITY_LEVEL = 128;
}