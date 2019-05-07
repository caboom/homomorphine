#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE backend

#include <iostream>
#include <boost/test/included/unit_test.hpp>

#include "../src/backend_factory.hpp"

using namespace std;
using namespace homomorphine;

// Test SEAL backend
BOOST_AUTO_TEST_CASE( test_constructor )
{
  BOOST_TEST_MESSAGE( "Testing a generic homomorphic encryption backend..." );

  Backend* backend = BackendFactory::create("seal");

  backend->setAlgorithm("BFV");
  backend->init();
}