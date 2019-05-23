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
  /*! /brief Utility class
   *
   * This class provides a various utility functions. At this moment it
   * supports UUEncoding/UUDecoding of the binary string streams used
   * to serialize various binary objects for external usage and standardization
   * of the interface.
   */
  class Util {
    public:
      /*!
       * Encodes the binary string stream to string
       * 
       * \param string_stream string stream to be UUEncoded
       * \return UUEncoded string
       */
      static const string uuencodeStream(stringstream &string_stream);

      /*!
       * Decodes UUEncoded string to a binary string stream
       * 
       * \param content UUENcoded string
       * \param string_stream stream containing a decoded stream
       */
      static const void uudecodeString(string content, stringstream &string_stream);
  };
}

#endif