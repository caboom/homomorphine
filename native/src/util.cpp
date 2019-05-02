#include "util.hpp"

namespace homomorphine 
{
  const string Util::uuencodeStream(stringstream &key_stream) 
  {
    stringstream uuencoded_stream;
    string key_string = key_stream.str();
    
    typedef 
      insert_linebreaks<         // insert line breaks every 72 characters
        base64_from_binary<    // convert binary values to base64 characters
          transform_width<   // retrieve 6 bit integers from a sequence of 8 bit bytes
            const char *,
            6,
            8
          >
        > 
        ,72
      > 
      base64_text; // compose all the above operations in to a new iterator

    std::copy(
      base64_text(key_string.c_str()),
      base64_text(key_string.c_str() + key_string.size()),
      boost::archive::iterators::ostream_iterator<char>(uuencoded_stream)
    ); 

    return uuencoded_stream.str();
  }

  const void Util::uudecodeString(string encoded_key, stringstream &key_stream)
  {
    typedef 
      transform_width< 
        binary_from_base64<
          remove_whitespace<
            const char *
          > 
        >,
        8,
        6 
      > 
      text_base64;

    std::copy(
      text_base64(encoded_key.c_str()),
      text_base64(encoded_key.c_str() + encoded_key.size()),
      boost::archive::iterators::ostream_iterator<char>(key_stream)
    ); 
  }
}