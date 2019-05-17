#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE clang

#include <string>
#include <iostream>
#include <boost/test/included/unit_test.hpp>

#include "../src/clang_types.hpp"
#include "../src/clang_backend_interface.hpp"

using namespace std;

//
// Test generic backend clang wrapper
//

BOOST_AUTO_TEST_CASE( test_backend_clang_interface )
{
  BOOST_TEST_MESSAGE ( "Test generic backend Clang interface..." );

  string algorithm = "bfv";
  string backend_name = "seal";

  // create the backends
  BackendWrapper wrapper = CreateBackend((char *)backend_name.c_str());
  BackendWrapper encrypt_wrapper = CreateBackend((char *)backend_name.c_str());

  // generate basic key pair
  SetBackendAlgorithm(wrapper, (char *)algorithm.c_str());
  InitBackend(wrapper);

  char **keys = GenerateBackendKeys(wrapper);

  // test the encryption
  SetBackendAlgorithm(encrypt_wrapper, (char *)algorithm.c_str());
  InitBackend(encrypt_wrapper);

  SetBackendPublicKey(encrypt_wrapper, keys[0]);
  BackendEncrypt(encrypt_wrapper, 10000);

  // do the basic numeric operations
  BackendAdd(encrypt_wrapper, 25);
  BackendNegate(encrypt_wrapper);
  BackendMultiply(encrypt_wrapper, 1000);

  // check the result
  SetBackendSecretKey(encrypt_wrapper, keys[1]);

  BOOST_TEST ( BackendDecrypt(encrypt_wrapper) == -10025000 );

  // clean the result
  FreeBackend(wrapper);
  FreeBackend(encrypt_wrapper);
}
