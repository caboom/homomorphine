#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE boolean circuit backend

#include <iostream>
#include <boost/test/included/unit_test.hpp>

#include "../src/boolean_circuit_backend.hpp"
#include "../src/boolean_circuit_backend_factory.hpp"

using namespace std;
using namespace homomorphine;

BOOST_AUTO_TEST_CASE( dummy_test )
{
  BOOST_TEST ( true );
}

//
// Tests for TFHE backend
//

#ifdef __HAS_TFHE__

// Basic TFHE backend test
BOOST_AUTO_TEST_CASE( tfhe_check_encryption )
{
  int value = 12228;
  stringstream cipher;
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
  backend->encrypt(value);
  backend->writeCipherToStream(cipher);

  // create new backend and initialize it
  BooleanCircuitBackend* public_backend = BooleanCircuitBackendFactory::create("tfhe");
  public_backend->init();
  public_backend->readPublicKeyFromStream(public_key);
  public_backend->readSecretKeyFromStream(secret_key);
  public_backend->readCipherFromStream(cipher);
 
  BOOST_TEST ( backend->decrypt() == public_backend->decrypt() );
}

#endif