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
  seal.generateSealKeys();

  // test generating uuencoded keys
  pair<string, string> keys = seal.generateKeys();
}

// SEAL backend serialization/deserialization test
BOOST_AUTO_TEST_CASE( serialization_deserialization_test )
{
  BOOST_TEST_MESSAGE( "Testing a SEAL backend serialization/deserialization..." );

  SealBackend seal_serialization;
  
  seal_serialization.setAlgorithm(SEAL_BFV);
  seal_serialization.init();

  // test generating regular keys
  seal_serialization.generateSealKeys();

  // test generating uuencoded keys
  pair<string, string> keys = seal_serialization.generateKeys();

  // create deserialization SEAL backend
  SealBackend seal_deserialization;

  seal_deserialization.setAlgorithm(SEAL_BFV);
  seal_deserialization.init();

  // add key
  seal_deserialization.setPublicKey(keys.first);
  seal_deserialization.setSecretKey(keys.second);

  // test serialization/deserialization
  pair<string, string> deserialized_keys = seal_deserialization.getKeys();

  BOOST_TEST ( keys.first == deserialized_keys.first );
  BOOST_TEST ( keys.second == deserialized_keys.second );
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
  seal.generateSealKeys();

  // test generating uuencoded keys
  pair<string, string> keys = seal.generateKeys();

  // encrypt using a new object
  SealBackend seal_encrypt;

  seal_encrypt.setAlgorithm(SEAL_BFV);
  seal_encrypt.init();

  seal_encrypt.setPublicKey(keys.first);
  seal_encrypt.encrypt(values);
}

// batch SEAL backend operations test
BOOST_AUTO_TEST_CASE( batch_operations_test )
{
  BOOST_TEST_MESSAGE( "Testing SEAL batch operations..." );

  vector<uint64_t> results;
  SealBackend seal;
  vector<uint64_t> values { 1000, 2000 };
  vector<uint64_t> add_to_values { 20, 50 };
  vector<uint64_t> add_to_values_again { 10, 20 };
  
  seal.setAlgorithm(SEAL_BFV);
  seal.init();

  // test generating uuencoded keys
  pair<string, string> keys = seal.generateKeys();

  // encrypt using a new object
  SealBackend seal_encrypt;

  seal_encrypt.setAlgorithm(SEAL_BFV);
  seal_encrypt.init();

  seal_encrypt.setPublicKey(keys.first);
  seal_encrypt.encrypt(values);

  // do some basic numeric operations
  seal_encrypt.add(add_to_values);
  seal_encrypt.add(add_to_values_again);

  // check the results
  seal_encrypt.setSecretKey(keys.second);
  results = seal_encrypt.decryptValues();

  BOOST_TEST ( results[0] == 1030 );
  BOOST_TEST ( results[1] == 2070 );
}

// single integer SEAL backend operation test
BOOST_AUTO_TEST_CASE( single_operation_test )
{
  BOOST_TEST_MESSAGE( "Testing SEAL operations on a single integer..." );

  int result;
  string cipher;
  SealBackend seal;
  
  seal.setAlgorithm(SEAL_BFV);
  seal.init();

  // test generating uuencoded keys
  pair<string, string> keys = seal.generateKeys();

  // encrypt using a new object
  SealBackend seal_encrypt;

  seal_encrypt.setAlgorithm(SEAL_BFV);
  seal_encrypt.init();

  seal_encrypt.setPublicKey(keys.first);
  seal_encrypt.encrypt(10000);

  // do some basic numeric operations
  seal_encrypt.add(20);
  seal_encrypt.multiply(50);
  seal_encrypt.negate();
  seal_encrypt.add(50);
  seal_encrypt.multiply(11);

  // check the results
  seal_encrypt.setSecretKey(keys.second);
  result = seal_encrypt.decrypt();

  BOOST_TEST ( result == -5510450 );

  // check cipher handling
  seal.setCipher(seal_encrypt.getCipher());
  result = seal.decrypt();

  BOOST_TEST ( result == -5510450 );
}
