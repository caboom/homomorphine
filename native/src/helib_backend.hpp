#ifndef _HOMOMORPHINE_HELIB_BACKED_H_
#define _HOMOMORPHINE_HELIB_BACKED_H_

#include <iostream>
#include <utility>
#include <sstream>
#include <string>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>

#include "util.hpp"
#include "backend.hpp"
#include "constants.hpp"

using namespace std;
using namespace boost::archive::iterators;

namespace homomorphine 
{
  enum HELibAlgorithmType { 
    HELIB_UNKNOWN
  }; 

  class HELibBackend : public Backend
  {
    private:

    public:
      ~HELibBackend();
      void setAlgorithm(string algorithm);
      void init();
      void generateKeys();
      string getPublicKey();
      string getSecretKey();
      pair<string, string> getKeys(); 
      void setPublicKey(string public_key);
      void setSecretKey(string secret_key);
      void setKeys(string public_key, string secret_key);
      string getCipher();
      void setCipher(string cipher);
      string encrypt(vector<int64_t> values); 
      string encrypt(int64_t value);
      vector<int64_t> decryptValues();
      int64_t decrypt();
      void add(vector<int64_t> values);
      void add(int64_t value);
      void negate();
      void multiply(vector<int64_t> values);
      void multiply(int64_t value);
  };
}

#endif