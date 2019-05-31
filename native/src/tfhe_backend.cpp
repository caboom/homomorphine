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

}