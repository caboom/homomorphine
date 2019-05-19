#include "helib_backend.hpp"

namespace homomorphine 
{
  HELibBackend::~HELibBackend() { }

  void HELibBackend::setAlgorithm(string algorithm) 
  {

  }
  
  void HELibBackend::init() 
  {

  }
      
  void HELibBackend::generateKeys()
  {

  }
      
  string HELibBackend::getPublicKey()
  {
    return "";
  }
  
  string HELibBackend::getSecretKey()
  {
    return "";
  } 
  
  pair<string, string> HELibBackend::getKeys()
  {
    pair<string, string> keys;

    return keys;
  } 
  
  void HELibBackend::setPublicKey(string public_key)
  {

  }
  
  void HELibBackend::setSecretKey(string secret_key)
  {

  }
  
  void HELibBackend::setKeys(string public_key, string secret_key)
  {

  }

  string HELibBackend::getCipher()
  {
    return "";
  }

  void HELibBackend::setCipher(string cipher)
  {

  }
      
  string HELibBackend::encrypt(vector<int64_t> values)
  {
    return "";
  }
      
  string HELibBackend::encrypt(int64_t value)
  {
    return "";
  }

  vector<int64_t> HELibBackend::decryptValues()
  {
    vector<int64_t> result;

    return result;
  }

  int64_t HELibBackend::decrypt()
  {
    return 0;
  }

  void HELibBackend::add(vector<int64_t> values)
  {

  }

  void HELibBackend::add(int64_t value)
  {

  }

  void HELibBackend::negate()
  {

  }

  void HELibBackend::multiply(vector<int64_t> values)
  {

  }

  void HELibBackend::multiply(int64_t value)
  {

  }
}