#ifndef _HOMOMORPHINE_UTIL_H_
#define _HOMOMORPHINE_UTIL_H_

#include <iostream>
#include <utility>
#include <sstream>
#include <string>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/insert_linebreaks.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/ostream_iterator.hpp>
#include <boost/archive/iterators/remove_whitespace.hpp>

using namespace std;
using namespace boost::archive::iterators;

namespace homomorphine 
{
  class Util {
    public:
      static const string uuencodeStream(stringstream &key_stream);
      static const void uudecodeString(string encoded_key, stringstream &key_stream);
  };
}

#endif