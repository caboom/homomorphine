#include "helib_backend.hpp"

namespace homomorphine 
{

  HELibBackend::~HELibBackend() { 
    delete(this->context);
  }

  void HELibBackend::setAlgorithm(string algorithm) 
  {
    this->algorithm = HELIB_DEFAULT_ALGORITHM; // there is only one atm
  }
  
  void HELibBackend::init() 
  {
    unsigned long prime_modulus;
    unsigned long cyclotomic_polynomial;
    unsigned long hensel_lifting;
    unsigned long modulus_chain_bits;
    unsigned long num_columns;

    // plaintext prime modulus
    params.count("prime_modulus") ?
      prime_modulus = stoi(this->params["prime_modulus"]) :
      prime_modulus = Constants::HELIB_PLAINTEXT_PRIME_MODULUS;

    // cyclotomic polynomial - defines phi(m)
    params.count("cyclotomic_polynomial") ?
      cyclotomic_polynomial = stoi(this->params["cyclotomic_polynomial"]) :
      cyclotomic_polynomial = Constants::HELIB_CYCLOTOMIC_POLYNOMIAL;

    // hensel lifting (default = 1)
    params.count("hensel_lifting") ?
      hensel_lifting = stoi(this->params["hensel_lifting"]) :
      hensel_lifting = Constants::HELIB_HENSEL_LIFTING;

    // number of bits of the modulus chain
    params.count("modulus_chain_bits") ?
      modulus_chain_bits = stoi(this->params["modulus_chain_bits"]) :
      modulus_chain_bits = Constants::HELIB_MODULUS_CHAIN_BITS;

    // number of columns of key-switching matix (default = 2 or 3)
    params.count("num_columns") ?
      num_columns = stoi(this->params["num_columns"]) :
      num_columns = Constants::HELIB_NUMBER_OF_COLUMNS;
  
    this->context = new FHEcontext(cyclotomic_polynomial, prime_modulus, hensel_lifting);
    buildModChain(*this->context, modulus_chain_bits, num_columns);
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