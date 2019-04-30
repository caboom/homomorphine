#ifndef _HOMOMORPHINE_SEAL_BACKED_H_
#define _HOMOMORPHINE_SEAL_BACKED_H_

#include <iostream>
#include <utility>
#include <sstream>
#include <string>
#include <seal/seal.h>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/insert_linebreaks.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/ostream_iterator.hpp>
#include <boost/archive/iterators/remove_whitespace.hpp>


#include "backend.hpp"
#include "constants.hpp"

using namespace seal;
using namespace std;
using namespace boost::archive::iterators;

namespace homomorphine 
{
  enum SealAlgorithmType { 
    SEAL_BFV, SEAL_CKKS, SEAL_UNKNOWN
  }; 

  class SealBackend : public Backend
  {
    private:
      std::shared_ptr<SEALContext> context;
      IntegerEncoder *encoder;
      KeyGenerator *keygen;
      SealAlgorithmType type;
      EncryptionParameters *encryption_params;
      PublicKey public_key;
      SecretKey secret_key;

      SealAlgorithmType getAlgorithmType(string name);
      void initBFV();
      string uuencodeStream(stringstream &key_stream);
      void uudecodeString(string encoded_key, stringstream &key_stream);

    public:
      ~SealBackend();
      void init();
      void setAlgorithm(string algorithm);
      void setAlgorithm(SealAlgorithmType algorithm);
      string generateEncodedPublicKey();
      string generateEncodedSecretKey();
      pair<string, string> generateEncodedKeys();
      vector<string> encrypt(string encoded_public_key, vector<int> values);

      PublicKey getPublicKey();
      SecretKey getSecretKey();
      pair<PublicKey, SecretKey> getKeys();
      void setPublicKey(PublicKey public_key);
      void setSecretKey(SecretKey secret_key);
      void setKeys(PublicKey public_key, SecretKey secret_key);
      PublicKey generatePublicKey();
      SecretKey generateSecretKey();
      pair<PublicKey, SecretKey> generateKeys();
  };
}

#endif