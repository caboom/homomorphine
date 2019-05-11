#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE clang

#include <string>
#include <iostream>
#include <boost/test/included/unit_test.hpp>

#include "../src/clang_types.hpp"
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
  uint_array_t values;
  uint_array_t add_to_values;
  uint_array_t multiply_with_values;

  uint64_t elements[2] = {1000ULL, 2000ULL};
  uint64_t add_to[2] = {20ULL, 50ULL};
  uint64_t multiply_with[2] = {10ULL, 20ULL};

  // set the values
  values.elements = elements;
  values.count = 2;

  add_to_values.elements = add_to;
  add_to_values.count = 2;

  multiply_with_values.elements = multiply_with;
  multiply_with_values.count = 2;

  // create the backends
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
  BackendEncrypt(encrypt_wrapper, values);

  // do the basic numeric operations
  BackendAdd(encrypt_wrapper, add_to_values);
  BackendNegate(encrypt_wrapper);
  BackendMultiply(encrypt_wrapper, multiply_with_values);

  // check the result
  BackendSetSecretKey(encrypt_wrapper, keys[1]);
  
  //BOOST_TEST ( BackendDecrypt(encrypt_wrapper) == -10200 );

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
  uint_array_t values;
  uint_array_t add_to_values;
  uint_array_t multiply_with_values;

  uint64_t elements[2] = {1000ULL, 2000ULL};
  uint64_t add_to[2] = {20ULL, 50ULL};
  uint64_t multiply_with[2] = {10ULL, 20ULL};

  // set the values
  values.elements = elements;
  values.count = 2;

  add_to_values.elements = add_to;
  add_to_values.count = 2;

  multiply_with_values.elements = multiply_with;
  multiply_with_values.count = 2;

  // create the backends
  SealWrapper wrapper = SealBackendCreate();
  SealWrapper encrypt_wrapper = SealBackendCreate();

  // set the values
  values.elements = elements;
  values.count = 2;

  // generate basic key pair
  SealBackendSetAlgorithm(wrapper, (char *)algorithm.c_str());
  SealBackendInit(wrapper);

  char **keys = SealBackendGenerateEncodedKeys(wrapper);

  // test the encryption
  SealBackendSetAlgorithm(encrypt_wrapper, (char *)algorithm.c_str());
  SealBackendInit(encrypt_wrapper);

  SealBackendSetPublicKey(encrypt_wrapper, keys[0]);
  SealBackendEncrypt(encrypt_wrapper, values);

  // do the basic numeric operations
  SealBackendAdd(encrypt_wrapper, add_to_values);
  SealBackendNegate(encrypt_wrapper);
  SealBackendMultiply(encrypt_wrapper, multiply_with_values);

  // check the result
  SealBackendSetSecretKey(encrypt_wrapper, keys[1]);
  
  //BOOST_TEST ( SealBackendDecrypt(encrypt_wrapper) == -10200 );

  // clean the result
  SealBackendFree(wrapper);
  SealBackendFree(encrypt_wrapper);
}
