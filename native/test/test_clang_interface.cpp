#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE clang

#include <string>
#include <iostream>
#include <boost/test/included/unit_test.hpp>

#include "../src/clang_backend_interface.hpp"
#include "../src/clang_seal_interface.hpp"

using namespace std;

//
// Test generic backend clang wrapper
//

BOOST_AUTO_TEST_CASE( test_backend_clang_interface )
{
  BOOST_TEST_MESSAGE ( "Test generic backend Clang interface..." );

  string algorithm = "bfv";
  string backend_name = "seal";

  BackendWrapper wrapper = BackendCreate((char *)backend_name.c_str());
  BackendWrapper encrypt_wrapper = BackendCreate((char *)backend_name.c_str());

  // generate basic key pair
  BackendSetAlgorithm(wrapper, (char *)algorithm.c_str());
  BackendInit(wrapper);

  char **keys = BackendGenerateEncodedKeys(wrapper);

  // test the encryption
  BackendSetAlgorithm(encrypt_wrapper, (char *)algorithm.c_str());
  BackendInit(encrypt_wrapper);

  BackendSetPublicKey(encrypt_wrapper, keys[0]);
  BackendEncryptValue(encrypt_wrapper, 1000);

  // do the basic numeric operations
  BackendAdd(encrypt_wrapper, 20);
  BackendNegate(encrypt_wrapper);
  BackendMultiply(encrypt_wrapper, 10);

  // check the result
  BackendSetSecretKey(encrypt_wrapper, keys[1]);
  
  BOOST_TEST ( BackendDecrypt(encrypt_wrapper) == -10200 );

  // clean the result
  BackendFree(wrapper);
  BackendFree(encrypt_wrapper);
}

//
// Test SEAL backend
//

BOOST_AUTO_TEST_CASE( test_seal_clang_interface )
{
  BOOST_TEST_MESSAGE ( "Test SEAL Clang interface..." );

  string algorithm = "bfv";
  SealWrapper wrapper = SealBackendCreate();
  SealWrapper encrypt_wrapper = SealBackendCreate();

  // generate basic key pair
  SealBackendSetAlgorithm(wrapper, (char *)algorithm.c_str());
  SealBackendInit(wrapper);

  char **keys = SealBackendGenerateEncodedKeys(wrapper);

  // test the encryption
  SealBackendSetAlgorithm(encrypt_wrapper, (char *)algorithm.c_str());
  SealBackendInit(encrypt_wrapper);

  SealBackendSetPublicKey(encrypt_wrapper, keys[0]);
  SealBackendEncryptValue(encrypt_wrapper, 1000);

  // do the basic numeric operations
  SealBackendAdd(encrypt_wrapper, 20);
  SealBackendNegate(encrypt_wrapper);
  SealBackendMultiply(encrypt_wrapper, 10);

  // check the result
  SealBackendSetSecretKey(encrypt_wrapper, keys[1]);
  
  BOOST_TEST ( SealBackendDecrypt(encrypt_wrapper) == -10200 );

  // clean the result
  SealBackendFree(wrapper);
  SealBackendFree(encrypt_wrapper);
}
