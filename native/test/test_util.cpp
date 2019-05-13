#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE util

#include <iostream>
#include <boost/test/included/unit_test.hpp>
#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include "../src/util.hpp"

using namespace std;
using namespace homomorphine;

#define TEST_RANDOM_STR_SIZE 10240

// Helper function
string generateRandomString(int len) {
  string rnd_string;

  std::string chars(
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "1234567890"
    "!@#$%^&*()"
    "`~-_=+[{]{\\|;:'\",<.>/? ");
  
  // generate random string
  boost::random::random_device rng;
  boost::random::uniform_int_distribution<> index_dist(0, chars.size() - 1);
  for(int i = 0; i < len; ++i) {
    rnd_string += chars[index_dist(rng)];
  }

  return rnd_string;
}

// Test SEAL backend
BOOST_AUTO_TEST_CASE( test_constructor )
{
  stringstream rnd_string_stream;
  stringstream decoded_rnd_string_stream;

  BOOST_TEST_MESSAGE( "Testing util class methods..." );

  // initialize random string
  string rnd_string = generateRandomString(TEST_RANDOM_STR_SIZE);
  rnd_string_stream << rnd_string; 

  // uuencode/decode random generated string
  string uuencoded_string = Util::uuencodeStream(rnd_string_stream);
  Util::uudecodeString(uuencoded_string, decoded_rnd_string_stream);
  
  BOOST_TEST( rnd_string == decoded_rnd_string_stream.str() );
}