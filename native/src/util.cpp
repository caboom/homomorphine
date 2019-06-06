#include "util.hpp"

namespace homomorphine 
{
  const string Util::uuencodeStream(stringstream &string_stream) 
  {
    stringstream uuencoded_stream;
    string encoded_string = string_stream.str();
    
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
      base64_text(encoded_string.c_str()),
      base64_text(encoded_string.c_str() + encoded_string.size()),
      boost::archive::iterators::ostream_iterator<char>(uuencoded_stream)
    ); 

    return uuencoded_stream.str();
  }

  const void Util::uudecodeString(string content, stringstream &string_stream)
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
      text_base64(content.c_str()),
      text_base64(content.c_str() + content.size()),
      boost::archive::iterators::ostream_iterator<char>(string_stream)
    ); 
  }

  const vector<int> Util::getRandomVector(int &size) 
  {
    vector<int> result(size);
    boost::random::mt19937 generator;
    boost::random::uniform_int_distribution<> distribution(numeric_limits<int>::min(), numeric_limits<int>::max());

    // seed the generator and generate random numbers
    generator.seed(time(0));

    for (int i = 0; i < size; i++) {
      result[i] = distribution(generator);
    }

    return result;
  }

  const long Util::getStreamSize(istream &stream)
  {
    long start, end;

    start = stream.tellg();
    stream.seekg (start, ios::end);
    end = stream.tellg();
    stream.seekg(start, ios::beg);

    return end - start;
  }

}