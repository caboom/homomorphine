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
  int value = 10321;

  BOOST_TEST_MESSAGE( "Testing a TFHE backend encryption..." );

  string public_key;
  string secret_key;
  BooleanCircuitBackend* backend = BooleanCircuitBackendFactory::create("tfhe");

  // initialize
  backend->init();

  // generate uuencoded keys
  backend->generateKeys();
  backend->encrypt(value);
  BOOST_TEST ( backend->decrypt() == value );
}

#endif