#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE boolean circuit backend

#include <iostream>
#include <boost/test/included/unit_test.hpp>

#include "../src/boolean_circuit_backend.hpp"
#include "../src/boolean_circuit_backend_factory.hpp"

using namespace std;
using namespace homomorphine;

//
// Tests for TFHE backend
//

#ifdef __HAS_TFHE__

// Basic TFHE backend test
BOOST_AUTO_TEST_CASE( tfhe_check_encryption )
{
  int value = 12228;
  stringstream cipher;
  stringstream test_cipher;
  stringstream public_key;
  stringstream secret_key;

  BOOST_TEST_MESSAGE( "Testing a TFHE backend encryption..." );

  // create and initialize backend
  BooleanCircuitBackend* backend = BooleanCircuitBackendFactory::create("tfhe");
  backend->init();

  // generate keys and get key streams
  backend->generateKeys();
  backend->writePublicKeyToStream(public_key);
  backend->writeSecretKeyToStream(secret_key);

  // encrypt the value and write cipher to a stream
  backend->encryptToStream(value, cipher);

  // create new backend and initialize it
  BooleanCircuitBackend* test_backend = BooleanCircuitBackendFactory::create("tfhe");
  test_backend->init();
  test_backend->readPublicKeyFromStream(public_key);
  test_backend->readSecretKeyFromStream(secret_key);
  test_backend->encryptToStream(value, test_cipher);
 
  BOOST_TEST ( backend->decryptFromStream(cipher) == test_backend->decryptFromStream(test_cipher) );
}

// Basic TFHE backend test
BOOST_AUTO_TEST_CASE( tfhe_check_simple_operation )
{
  int value = 16;
  stringstream cipher;
  stringstream result_cipher;
  stringstream public_key;
  stringstream secret_key;

  BOOST_TEST_MESSAGE( "Testing a simple TFHE operations..." );

  // create and initialize backend
  BooleanCircuitBackend* backend = BooleanCircuitBackendFactory::create("tfhe");
  backend->init();

  // generate keys and get key streams
  backend->generateKeys();
  backend->writePublicKeyToStream(public_key);
  backend->writeSecretKeyToStream(secret_key);

  // encrypt the value and write cipher to a stream
  backend->encryptToStream(value, cipher);

  // create new backend and initialize it
  BooleanCircuitBackend* test_backend = BooleanCircuitBackendFactory::create("tfhe");
  test_backend->init();
  test_backend->readPublicKeyFromStream(public_key);
  test_backend->NOT(result_cipher, cipher);
 
  // decrypt the value and veryf the result
  BOOST_TEST ( backend->decryptFromStream(result_cipher) == 65519 );
}

// Basic TFHE backend test
BOOST_AUTO_TEST_CASE( tfhe_check_AND_operation_with_public_encoding )
{
  int value_x = 2069;   // 0000100000010101
  int value_y = 143;    // 0000000010001111
  stringstream cipher_x;
  stringstream cipher_y;
  stringstream result_cipher;
  stringstream public_key;
  stringstream secret_key;

  BOOST_TEST_MESSAGE( "Testing a AND TFHE operation - encoding at public end..." );

  // create and initialize backend
  BooleanCircuitBackend* backend = BooleanCircuitBackendFactory::create("tfhe");
  backend->init();

  // generate keys and get key streams
  backend->generateKeys();
  backend->writePublicKeyToStream(public_key);
  backend->writeSecretKeyToStream(secret_key);

  // encrypt the value and write cipher to a stream
  backend->encryptToStream(value_x, cipher_x);

  // create new backend and initialize it
  BooleanCircuitBackend* test_backend = BooleanCircuitBackendFactory::create("tfhe");
  test_backend->init();
  test_backend->readPublicKeyFromStream(public_key);

  // encode the value and write cipher to a stream
  test_backend->encodeToStream(value_y, cipher_y);

  test_backend->AND(result_cipher, cipher_x, cipher_y);
  
  // decrypt the value and veryf the result
  BOOST_TEST ( backend->decryptFromStream(result_cipher) == (value_x & value_y) );
}

#endif