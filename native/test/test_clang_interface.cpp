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
  BackendEncrypt(encrypt_wrapper, values);

  // do the basic numeric operations
  BackendAdd(encrypt_wrapper, add_to_values);
  BackendNegate(encrypt_wrapper);
  BackendMultiply(encrypt_wrapper, multiply_with_values);

  // check the result
  SetBackendSecretKey(encrypt_wrapper, keys[1]);
  
  //BOOST_TEST ( BackendDecrypt(encrypt_wrapper) == -10200 );

  // clean the result
  FreeBackend(wrapper);
  FreeBackend(encrypt_wrapper);
}
