#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE backend

#include <iostream>
#include <boost/test/included/unit_test.hpp>

#include "../src/backend_factory.hpp"

using namespace std;
using namespace homomorphine;

// Test SEAL backend
BOOST_AUTO_TEST_CASE( simple_seal_backend_test )
{
  BOOST_TEST_MESSAGE( "Testing a generic homomorphic encryption backend (SEAL implementation)..." );

  long result;
  string public_key;
  string secret_key;
  Backend* backend = BackendFactory::create("seal");

  backend->setAlgorithm("BFV");
  backend->init();

  // generate uuencoded keys
  backend->generateKeys();
  public_key = backend->getPublicKey();
  secret_key = backend->getSecretKey();

  // encrypt using a new object
  Backend* backend_operations = BackendFactory::create("seal");

  backend_operations->setAlgorithm("BFV");
  backend_operations->init();

  backend_operations->setPublicKey(public_key);
  backend_operations->encrypt(10000);

  // do some basic numeric operations
  backend_operations->add(20);
  backend_operations->multiply(50);
  backend_operations->negate();
  backend_operations->add(50);
  backend_operations->multiply(11);

  // check the results
  backend_operations->setSecretKey(secret_key);
  result = backend_operations->decrypt();

  BOOST_TEST ( result == -5510450 );

  // cleanup
  delete(backend);
  delete(backend_operations);
}

// Test HELib backend
BOOST_AUTO_TEST_CASE( simple_helib_backend_test )
{
  BOOST_TEST_MESSAGE( "Testing a generic homomorphic encryption backend (HELib implementation)..." );

  int result;
  string cipher;
  string public_key;
  string secret_key;

  // initialize HELib backend
  Backend* backend = BackendFactory::create("helib");
  backend->init();

  // generate keys
  backend->generateKeys();
  public_key = backend->getPublicKey();
  secret_key = backend->getSecretKey();
  cipher = backend->encrypt(10);

  // encrypt using a new object
  Backend* backend_operations = BackendFactory::create("helib");
  backend_operations->init();

  backend_operations->setPublicKey(public_key);
  backend_operations->setCipher(cipher);

  // do some basic numeric operations
  backend_operations->add(10);
  backend_operations->multiply(5);

  cipher = backend_operations->getCipher();

  // check the results
  backend->setCipher(cipher);
  result = backend->decrypt();

  // TODO - still not working properly

  // cleanup
  delete(backend);
  delete(backend_operations);
}