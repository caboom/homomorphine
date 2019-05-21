#ifndef _HOMOMORPHINE_HELIB_BACKED_H_
#define _HOMOMORPHINE_HELIB_BACKED_H_

#include <iostream>
#include <utility>
#include <sstream>
#include <string>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>
#include <helib/FHE.h>
#include <helib/EncryptedArray.h>

#include "util.hpp"
#include "backend.hpp"
#include "constants.hpp"

using namespace NTL;
using namespace std;
using namespace boost::archive::iterators;

namespace homomorphine 
{
  enum HELibAlgorithmType { 
    HELIB_DEFAULT_ALGORITHM
  }; 

  class HELibBackend : public Backend
  {
    private:
      std::unique_ptr<FHEcontext> context = nullptr;
      FHEPubKey* public_key = nullptr;
      FHESecKey* secret_key = nullptr;
      ZZX polynomial;
      std::unique_ptr<Ctxt> cipher = nullptr;
      HELibAlgorithmType algorithm;

      unsigned long hamming_weight;

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
      string encrypt(vector<long> values); 
      string encrypt(long value);
      vector<long> decryptValues();
      long decrypt();
      void add(vector<long> values);
      void add(long value);
      void negate();
      void multiply(vector<long> values);
      void multiply(long value);
  };
}

#endif