#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE seal

#include <string>
#include <iostream>
#include <utility>
#include <iostream>
#include <exception>
#include <boost/test/included/unit_test.hpp>

#include "../src/seal_backend.hpp"

using namespace std;
using namespace homomorphine;

// Test SEAL backend
BOOST_AUTO_TEST_CASE( test_constructor )
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