#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE seal

#include <string>
#include <iostream>
#include <utility>
#include <iostream>
#include <exception>
#include <boost/test/included/unit_test.hpp>

#include "../src/seal_backend.hpp"
#include "../src/util.hpp"

using namespace std;
using namespace homomorphine;

// Basic SEAL backend test
BOOST_AUTO_TEST_CASE( basic_test )
{
  BOOST_TEST_MESSAGE( "Testing a SEAL homomorphic encryption backend..." );

  SealBackend seal;
  
  seal.setAlgorithm(SEAL_BFV);
  seal.init();

  // test generating regular keys
  seal.generateKeys();

  // test generating uuencoded keys
  pair<string, string> keys = seal.generateEncodedKeys();
}

// SEAL backend serialization/deserialization test
BOOST_AUTO_TEST_CASE( serialization_deserialization_test )
{
  BOOST_TEST_MESSAGE( "Testing a SEAL backend serialization/deserialization..." );

  SealBackend seal_serialization;
  
  seal_serialization.setAlgorithm(SEAL_BFV);
  seal_serialization.init();

  // test generating regular keys
  seal_serialization.generateKeys();

  // test generating uuencoded keys
  pair<string, string> keys = seal_serialization.generateEncodedKeys();

  // create deserialization SEAL backend
  SealBackend seal_deserialization;

  seal_deserialization.setAlgorithm(SEAL_BFV);
  seal_deserialization.init();

  // add key
  seal_deserialization.setPublicKey(keys.first);
  seal_deserialization.setSecretKey(keys.second);
}

// SEAL backend encryption test
BOOST_AUTO_TEST_CASE( encryption_test )
{
  BOOST_TEST_MESSAGE( "Testing a SEAL encryption..." );

  SealBackend seal;
  
  seal.setAlgorithm(SEAL_BFV);
  seal.init();

  // test generating regular keys
  seal.generateKeys();

  // test generating uuencoded keys
  pair<string, string> keys = seal.generateEncodedKeys();

  // encrypt using a new object
  SealBackend seal_encrypt;

  seal_encrypt.setAlgorithm(SEAL_BFV);
  seal_encrypt.init();

  seal_encrypt.setPublicKey(keys.first);
  seal_encrypt.encryptValue(1000);
}

// SEAL backend encryption test
BOOST_AUTO_TEST_CASE( operations_test )
{
  BOOST_TEST_MESSAGE( "Testing a SEAL encryption..." );

  int result;
  SealBackend seal;
  
  seal.setAlgorithm(SEAL_BFV);
  seal.init();

  // test generating regular keys
  seal.generateKeys();

  // test generating uuencoded keys
  pair<string, string> keys = seal.generateEncodedKeys();

  // encrypt using a new object
  SealBackend seal_encrypt;

  seal_encrypt.setAlgorithm(SEAL_BFV);
  seal_encrypt.init();

  seal_encrypt.setPublicKey(keys.first);
  seal_encrypt.encryptValue(1000);

  seal_encrypt.add(20);
  seal_encrypt.negate();
  seal_encrypt.multiply(10);

  seal_encrypt.setSecretKey(keys.second);
  
  BOOST_TEST_MESSAGE( "==== VALUE:" );
  BOOST_TEST_MESSAGE( seal_encrypt.decrypt() );
}