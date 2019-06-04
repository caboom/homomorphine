#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE arithmetic backend

#include <iostream>
#include <boost/test/included/unit_test.hpp>

#include "../src/arithmetic_backend.hpp"
#include "../src/arithmetic_backend_factory.hpp"

using namespace std;
using namespace homomorphine;

//
// Tests for SEAL backend
//

#ifdef __HAS_SEAL__

// Test SEAL backend
BOOST_AUTO_TEST_CASE( simple_seal_bfv_backend_test )
{
  BOOST_TEST_MESSAGE( "Testing a generic homomorphic encryption backend (SEAL implementation with BFV)..." );

  long result;
  stringstream public_key;
  stringstream secret_key;
  ArithmeticBackend* backend = ArithmeticBackendFactory::create("seal");

  backend->setAlgorithm("BFV");
  backend->init();

  // generate uuencoded keys
  backend->generateKeys();
  backend->writePublicKeyToStream(public_key);
  backend->writeSecretKeyToStream(secret_key);

  // encrypt using a new object
  ArithmeticBackend* backend_operations = ArithmeticBackendFactory::create("seal");

  backend_operations->setAlgorithm("BFV");
  backend_operations->init();

  backend_operations->readPublicKeyFromStream(public_key);
  backend_operations->encrypt(10000);

  // do some basic numeric operations
  backend_operations->add(20);
  backend_operations->multiply(50);
  backend_operations->negate();
  backend_operations->add(50);
  backend_operations->multiply(11);

  // check the results
  backend_operations->readSecretKeyFromStream(secret_key);
  result = backend_operations->decrypt();

  BOOST_TEST ( result == -5510450 );

  // cleanup
  delete(backend);
  delete(backend_operations);
}

BOOST_AUTO_TEST_CASE( simple_seal_ckks_backend_test )
{
  BOOST_TEST_MESSAGE( "Testing a generic homomorphic encryption backend (SEAL implementation with CKKS)..." );

  long result;
  stringstream public_key;
  stringstream secret_key;
  ArithmeticBackend* backend = ArithmeticBackendFactory::create("seal");

  backend->setAlgorithm("CKKS");
  backend->init();

  // generate uuencoded keys
  backend->generateKeys();
  backend->writePublicKeyToStream(public_key);
  backend->writeSecretKeyToStream(secret_key);

  // encrypt using a new object
  ArithmeticBackend* backend_operations = ArithmeticBackendFactory::create("seal");

  backend_operations->setAlgorithm("CKKS");
  backend_operations->init();

  backend_operations->readPublicKeyFromStream(public_key);
  backend_operations->encrypt(10);

  // do some basic numeric operations
  backend_operations->add(20);
  backend_operations->negate();
  backend_operations->add(50);

  // check the results
  backend_operations->readSecretKeyFromStream(secret_key);
  result = backend_operations->decrypt();

  BOOST_TEST ( result == 20 );

  // cleanup
  delete(backend);
  delete(backend_operations);
}
#endif

//
// Tests for HELib backend
//

#ifdef __HAS_HELIB__
// Test HELib backend
BOOST_AUTO_TEST_CASE( simple_helib_backend_test )
{
  BOOST_TEST_MESSAGE( "Testing a generic homomorphic encryption backend (HELib implementation)..." );

  int result;
  stringstream cipher;
  stringstream public_key;
  stringstream secret_key;

  // initialize HELib backend
  ArithmeticBackend* backend = ArithmeticBackendFactory::create("helib");
  backend->init();

  // generate keys
  backend->generateKeys();
  backend->writePublicKeyToStream(public_key);
  backend->writeSecretKeyToStream(secret_key);
  backend->encrypt(10);


  // encrypt using a new object
  ArithmeticBackend* backend_operations = ArithmeticBackendFactory::create("helib");
  backend_operations->init();

  backend_operations->readPublicKeyFromStream(public_key);
  backend_operations->setCipher(backend->getCipher());

  // do some basic numeric operations
  backend_operations->add(10);
  backend_operations->multiply(5);

  backend_operations->writeCipherToStream(cipher);

  // check the results
  backend->readCipherFromStream(cipher);
  result = backend->decrypt();

  // TODO - still not working properly

  // cleanup
  delete(backend);
  delete(backend_operations);
}
#endif