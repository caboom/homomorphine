#include "tfhe_backend.hpp"

namespace homomorphine {
  
  TFHEBackend::~TFHEBackend()
  {

  }

  void TFHEBackend::setAlgorithm(string algorithm)
  {

  }

  void TFHEBackend::init()
  {

  }

  void TFHEBackend::generateKeys()  
  {

  }

  string TFHEBackend::getPublicKey()
  {
    return "";  
  }

  string TFHEBackend::getSecretKey()
  {
    return "";
  }

  pair<string, string> TFHEBackend::getKeys()
  {
    return pair<string, string> ("", "");
  }

  void TFHEBackend::setPublicKey(string public_key)
  {

  }

  void TFHEBackend::setSecretKey(string secret_key)
  {

  }

  void TFHEBackend::setKeys(string public_key, string secret_key)
  {

  }

  string TFHEBackend::getCipher()
  {
    return "";
  }

  void TFHEBackend::setCipher(string cipher)
  {

  }

  string TFHEBackend::encrypt(vector<long> values)
  {
    return "";
  }

  string TFHEBackend::encrypt(long value)
  {
    return "";
  }

  vector<long> TFHEBackend::decryptValues()
  {
    return vector<long>();
  }

  long TFHEBackend::decrypt()
  {
    return 0;
  }

  void TFHEBackend::add(vector<long> values)
  {

  }

  void TFHEBackend::add(long value)
  {

  }

  void TFHEBackend::negate()
  {

  }

  void TFHEBackend::multiply(vector<long> values)
  {

  }

  void TFHEBackend::multiply(long value)
  {

  }

}