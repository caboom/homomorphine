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

// SEAL backend serialization/deserialization test
BOOST_AUTO_TEST_CASE( serialization_deserialization_test )
{
  BOOST_TEST_MESSAGE( "Testing a SEAL backend serialization/deserialization..." );

  string public_key;
  string secret_key;
  string deserialized_public_key;
  string deserialized_secret_key;
  SealBackend seal;
  SealBackend seal_deserialization;
  
  // generate keys
  seal.setAlgorithm(SEAL_BFV);
  seal.init();

  seal.generateKeys();
  public_key = seal.getPublicKey();
  secret_key = seal.getSecretKey();

  // create deserialization SEAL backend
  seal_deserialization.setAlgorithm(SEAL_BFV);
  seal_deserialization.init();

  // add key
  seal_deserialization.setPublicKey(public_key);
  seal_deserialization.setSecretKey(secret_key);

  // test serialization/deserialization
  deserialized_public_key = seal_deserialization.getPublicKey();
  deserialized_secret_key = seal_deserialization.getSecretKey();

  BOOST_TEST ( public_key == deserialized_public_key );
  BOOST_TEST ( secret_key == deserialized_secret_key );
}

// batch SEAL backend operations test
BOOST_AUTO_TEST_CASE( batch_operations_test )
{
  BOOST_TEST_MESSAGE( "Testing SEAL batch operations..." );

  vector<long> results;
  string public_key;
  string secret_key;
  SealBackend seal;
  vector<long> values { 1000, 2000 };
  vector<long> add_to_values { 20, 50 };
  vector<long> add_to_values_again { 10, 20 };
  
  seal.setAlgorithm(SEAL_BFV);
  seal.init();

  // test generating uuencoded keys
  seal.generateKeys();
  public_key = seal.getPublicKey();
  secret_key = seal.getSecretKey();

  // encrypt using a new object
  SealBackend seal_encrypt;

  seal_encrypt.setAlgorithm(SEAL_BFV);
  seal_encrypt.init();

  seal_encrypt.setPublicKey(public_key);
  seal_encrypt.encrypt(values);

  // do some basic numeric operations
  seal_encrypt.add(add_to_values);
  seal_encrypt.add(add_to_values_again);

  // check the results
  seal_encrypt.setSecretKey(secret_key);
  results = seal_encrypt.decryptValues();

  BOOST_TEST ( results[0] == 1030 );
  BOOST_TEST ( results[1] == 2070 );
}

// single integer SEAL backend operation test
BOOST_AUTO_TEST_CASE( single_operation_test )
{
  BOOST_TEST_MESSAGE( "Testing SEAL operations on a single integer..." );

  int result;
  string public_key;
  string secret_key;
  string cipher;
  SealBackend seal;
  
  seal.setAlgorithm(SEAL_BFV);
  seal.init();

  // test generating uuencoded keys
  seal.generateKeys();
  public_key = seal.getPublicKey();
  secret_key = seal.getSecretKey();

  // encrypt using a new object
  SealBackend seal_encrypt;

  seal_encrypt.setAlgorithm(SEAL_BFV);
  seal_encrypt.init();

  seal_encrypt.setPublicKey(public_key);
  seal_encrypt.encrypt(10000);

  // do some basic numeric operations
  seal_encrypt.add(20);
  seal_encrypt.multiply(50);
  seal_encrypt.negate();
  seal_encrypt.add(50);
  seal_encrypt.multiply(11);

  // check the results
  seal_encrypt.setSecretKey(secret_key);
  result = seal_encrypt.decrypt();

  BOOST_TEST ( result == -5510450 );

  // check cipher handling
  seal.setCipher(seal_encrypt.getCipher());
  result = seal.decrypt();

  BOOST_TEST ( result == -5510450 );
}
