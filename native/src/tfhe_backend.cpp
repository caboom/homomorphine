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

  void TFHEBackend::NOT(int value)
  {

  }

  void TFHEBackend::COPY(int value)
  {

  }

  void TFHEBackend::NAND(int value)
  {

  }

  void TFHEBackend::OR(int value)
  {

  }

  void TFHEBackend::AND(int value)
  {

  }

  void TFHEBackend::XOR(int value)
  {

  }

  void TFHEBackend::XNOR(int value)
  {

  }

  void TFHEBackend::NOR(int value)
  {

  }

  void TFHEBackend::ADDNY(int value)
  {

  }

  void TFHEBackend::ADDYN(int value)
  {

  }

  void TFHEBackend::ORNY(int value)
  {

  }

  void TFHEBackend::ORYN(int value)
  {

  }

  void TFHEBackend::MUX(int a, int b)
  {

  }

}