#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE clang

#include <string>
#include <iostream>
#include <boost/test/included/unit_test.hpp>

#include "../src/clang_interface.hpp"

using namespace std;

// Test SEAL backend
BOOST_AUTO_TEST_CASE( test_clang_interface )
{
  BOOST_TEST_MESSAGE ( "Test Clang interface..." );

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
