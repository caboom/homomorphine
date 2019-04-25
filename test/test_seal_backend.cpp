#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "Seal Backend Test"

#include <iostream>
#include <boost/test/unit_test.hpp>

#include "../src/seal_backend.hpp"

using namespace std;
using namespace homomorphine;

// Test SEAL backend
BOOST_AUTO_TEST_CASE( constructors )
{
  SealBackend seal;
  
  seal.setAlgorithm(SEAL_BFV);
  seal.init();
}