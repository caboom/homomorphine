#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE clang_boolean_circuit

#include <string>
#include <iostream>
#include <boost/test/included/unit_test.hpp>

#include "../src/info.hpp"
#include "../src/clang_types.hpp"
#include "../src/clang_boolean_circuit_backend_interface.hpp"

using namespace std;

BOOST_AUTO_TEST_CASE( dummy_test )
{
  BOOST_TEST ( true );
}

//
// Test boolean circuit backend clang wrapper
//

#ifdef __HAS_TFHE__

BOOST_AUTO_TEST_CASE( test_boolean_circuit_backend_clang_interface )
{
  string backend_name = "tfhe";

  BOOST_TEST_MESSAGE ( "Test boolean_circuit backend Clang interface..." );

  // create the backends
  BooleanCircuitBackendWrapper wrapper = CreateBooleanCircuitBackend((char *)backend_name.c_str());
  BooleanCircuitBackendWrapper encrypt_wrapper = CreateBooleanCircuitBackend((char *)backend_name.c_str());

  // generate basic key pair
  InitBooleanCircuitBackend(wrapper);

  GenerateBooleanCircuitBackendKeys(wrapper);
  char* public_key = GetBooleanCircuitBackendPublicKey(wrapper);
  char* secret_key = GetBooleanCircuitBackendSecretKey(wrapper);
}

#endif