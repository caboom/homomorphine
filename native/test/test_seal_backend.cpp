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
  vector<uint64_t> values { 1000ULL, 2000ULL };
  
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
  seal_encrypt.encrypt(values);
}

// SEAL backend encryption test
BOOST_AUTO_TEST_CASE( operations_test )
{
  BOOST_TEST_MESSAGE( "Testing a SEAL encryption..." );

  int result;
  SealBackend seal;
  vector<uint64_t> values { 1000ULL, 2000ULL };
  vector<uint64_t> add_to_values { 20ULL, 50ULL };
  vector<uint64_t> multiply_with_values { 10ULL, 20ULL };
  
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
  seal_encrypt.encrypt(values);

  // do some basic numeric operations
  seal_encrypt.add(add_to_values);
  seal_encrypt.multiply(multiply_with_values);

  seal_encrypt.setSecretKey(keys.second);
 
  // check the result
  //BOOST_TEST ( seal_encrypt.decrypt() == -10200 );
}