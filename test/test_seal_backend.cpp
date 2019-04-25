#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "Seal Backend Test"

#include <boost/test/unit_test.hpp>

// Test SEAL backend
BOOST_AUTO_TEST_CASE( constructors )
{
  BOOST_CHECK(10 == 20);
}