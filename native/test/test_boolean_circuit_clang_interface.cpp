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
  int value = 16;
  Blob cipher;
  Blob result_cipher;
  string backend_name = "tfhe";

  BOOST_TEST_MESSAGE ( "Test boolean_circuit backend Clang interface..." );

  // create the backends
  BooleanCircuitBackendWrapper wrapper = CreateBooleanCircuitBackend((char *)backend_name.c_str());
  BooleanCircuitBackendWrapper encrypt_wrapper = CreateBooleanCircuitBackend((char *)backend_name.c_str());

  // generate basic key pair
  InitBooleanCircuitBackend(wrapper);

  GenerateBooleanCircuitBackendKeys(wrapper);
  Blob public_key = GetBooleanCircuitBackendPublicKey(wrapper);
  Blob secret_key = GetBooleanCircuitBackendSecretKey(wrapper);

  // encrypt the value and write cipher to a stream
  cipher = BooleanCircuitEncrypt(wrapper, value);

  // test the encryption
  InitBooleanCircuitBackend(encrypt_wrapper);

  SetBooleanCircuitBackendPublicKey(encrypt_wrapper, public_key);
  result_cipher = BooleanCircuitNOT(encrypt_wrapper, cipher);

  // decrypt the value and veryf the result
  BOOST_TEST ( BooleanCircuitDecrypt(wrapper, result_cipher) == 65519 );
}

#endif