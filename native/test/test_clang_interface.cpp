#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE clang

#include <string>
#include <iostream>
#include <boost/test/included/unit_test.hpp>

#include "../src/clang_types.hpp"
#include "../src/clang_arithmetic_backend_interface.hpp"

using namespace std;

BOOST_AUTO_TEST_CASE( dummy_test )
{
  BOOST_TEST ( true );
}

//
// Test generic backend clang wrapper
//

#ifdef __HAS_SEAL__
BOOST_AUTO_TEST_CASE( test_backend_clang_interface )
{
  BOOST_TEST_MESSAGE ( "Test generic backend Clang interface..." );

  string algorithm = "bfv";
  string backend_name = "seal";

  // create the backends
  ArithmeticBackendWrapper wrapper = CreateArithmeticBackend((char *)backend_name.c_str());
  ArithmeticBackendWrapper encrypt_wrapper = CreateArithmeticBackend((char *)backend_name.c_str());

  // generate basic key pair
  SetArithmeticBackendAlgorithm(wrapper, (char *)algorithm.c_str());
  InitArithmeticBackend(wrapper);

  GenerateArithmeticBackendKeys(wrapper);
  char* public_key = GetArithmeticBackendPublicKey(wrapper);
  char* secret_key = GetArithmeticBackendSecretKey(wrapper);

  // test the encryption
  SetArithmeticBackendAlgorithm(encrypt_wrapper, (char *)algorithm.c_str());
  InitArithmeticBackend(encrypt_wrapper);

  SetArithmeticBackendPublicKey(encrypt_wrapper, public_key);
  ArithmeticBackendEncrypt(encrypt_wrapper, 10000);

  // do the basic numeric operations
  ArithmeticBackendAdd(encrypt_wrapper, 25);
  ArithmeticBackendNegate(encrypt_wrapper);
  ArithmeticBackendMultiply(encrypt_wrapper, 1000);

  // check the result
  SetArithmeticBackendSecretKey(encrypt_wrapper, secret_key);

  BOOST_TEST ( ArithmeticBackendDecrypt(encrypt_wrapper) == -10025000 );

  // clean the result
  FreeArithmeticBackend(wrapper);
  FreeArithmeticBackend(encrypt_wrapper);
}
#endif
