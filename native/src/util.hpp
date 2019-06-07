#ifndef _HOMOMORPHINE_UTIL_H_
#define _HOMOMORPHINE_UTIL_H_

#include <limits>
#include <ctime> 
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
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include "clang_types.hpp"

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

      /*!
       * Generates a vector of random values
       * 
       * \param size size of vector
       * \return vector of random numbers
       */
      static const vector<int> getRandomVector(int &size);

      /*!
       * Returns total size of input stream in bytes
       * 
       * \param stream input stream size
       * \return stream size in bytes
       */
      static const long getStreamSize(istream &stream);

      /*!
       * Loads the content of stream to bytes structure - required for handling 
       * byte streams that can't be simply copied into strings, or char arrays
       * without additional encoding 
       * 
       * \param stream input stream
       * \return bytes POD structure  
       */
      static const bytes copyStreamToBytes(istream& stream);
  };
}

#endif