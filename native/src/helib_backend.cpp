#include "helib_backend.hpp"

namespace homomorphine 
{

  HELibBackend::~HELibBackend() { }

  void HELibBackend::setAlgorithm(string algorithm) 
  {
    this->algorithm = HELibAlgorithm::DEFAULT; // there is only one atm
  }
  
  void HELibBackend::init() 
  {
    unsigned long prime_modulus;
    unsigned long cyclotomic_polynomial;
    unsigned long hensel_lifting;
    unsigned long modulus_chain_bits;
    unsigned long num_columns;
    unsigned long security_level;
    unsigned long degree_field_extension;
    unsigned long min_num_slots;

    // plaintext prime modulus
    params.count("prime_modulus") ?
      prime_modulus = stoul(this->params["prime_modulus"]) :
      prime_modulus = Constants::HELIB_PLAINTEXT_PRIME_MODULUS;

    // hensel lifting (default = 1)
    params.count("hensel_lifting") ?
      hensel_lifting = stoul(this->params["hensel_lifting"]) :
      hensel_lifting = Constants::HELIB_HENSEL_LIFTING;

    // number of bits of the modulus chain
    params.count("modulus_chain_bits") ?
      modulus_chain_bits = stoul(this->params["modulus_chain_bits"]) :
      modulus_chain_bits = Constants::HELIB_MODULUS_CHAIN_BITS;

    // number of columns of key-switching matix (default = 2 or 3)
    params.count("num_columns") ?
      num_columns = stoul(this->params["num_columns"]) :
      num_columns = Constants::HELIB_NUMBER_OF_COLUMNS;

    // hamming weight for key generation
    params.count("hamming_weight") ?
      this->hamming_weight = stoul(this->params["hamming_weight"]) :
      this->hamming_weight = Constants::HELIB_HAMMING_WEIGHT;

    // hamming weight for key generation
    params.count("security_level") ?
      security_level = stoi(this->params["security_level"]) :
      security_level = Constants::HELIB_SECURITY_LEVEL;

    // hamming weight for key generation
    params.count("degree_field_extension") ?
      degree_field_extension = stoi(this->params["degree_field_extension"]) :
      degree_field_extension = Constants::HELIB_DEGREE_OF_FIELD_EXTENSION;
    
    // hamming weight for key generation
    params.count("min_num_slots") ?
      min_num_slots = stoi(this->params["min_num_slots"]) :
      min_num_slots = Constants::HELIB_MINIMUM_NUMBER_OF_SLOTS;
  
    // initialize proper polynomial modulus, context and key builders
    cyclotomic_polynomial = FindM(
      security_level,
      modulus_chain_bits,
      num_columns,
      prime_modulus,
      degree_field_extension,
      min_num_slots,
      0
    );

    // initialize, or reset context
    if (this->context != nullptr) {
      delete(context);
    } 
    this->context = new FHEcontext(
      cyclotomic_polynomial, 
      prime_modulus, 
      hensel_lifting
    );

    // build chain and init polynomial
    buildModChain(*this->context, modulus_chain_bits, num_columns);
    this->polynomial = this->context->alMod.getFactorsOverZZ()[0]; 

    // initialize key pair
    this->generateKeys(); 
  }
      
  void HELibBackend::generateKeys()
  {
    if (this->secret_key != nullptr) {
      delete(this->secret_key);
    }

    this->secret_key = new FHESecKey(*this->context);
    this->secret_key->GenSecKey(this->hamming_weight);
    addSome1DMatrices(*this->secret_key);
    this->public_key = &*this->secret_key;
  }
      
  string HELibBackend::getPublicKey()
  {
    stringstream key_stream;
    writePubKeyBinary(key_stream, *this->public_key);

    return Util::uuencodeStream(key_stream); 
  }

  void HELibBackend::writePublicKeyToStream(ostream& stream)
  {
    writePubKeyBinary(stream, *this->public_key);
  }
  
  string HELibBackend::getSecretKey()
  {
    stringstream key_stream;
    writeSecKeyBinary(key_stream, *this->secret_key);

    return Util::uuencodeStream(key_stream); 
  } 

  void HELibBackend::writeSecretKeyToStream(ostream& stream)
  {
    writeSecKeyBinary(stream, *this->secret_key); 
  }
  
  pair<string, string> HELibBackend::getKeys()
  {
    return pair<string, string> (this->getPublicKey(), this->getSecretKey());
  } 
  
  void HELibBackend::setPublicKey(string public_key)
  {
    stringstream key_stream;
    Util::uudecodeString(public_key, key_stream);

    readPubKeyBinary(key_stream, *this->public_key);
  }

  void HELibBackend::readPublicKeyFromStream(istream &stream)
  {
    readPubKeyBinary(stream, *this->public_key);
  }
  
  void HELibBackend::setSecretKey(string secret_key)
  {
    stringstream key_stream;
    Util::uudecodeString(secret_key, key_stream);

    readSecKeyBinary(key_stream, *this->secret_key);
  }

  void HELibBackend::readSecretKeyFromStream(istream &stream)
  {
    readSecKeyBinary(stream, *this->secret_key);
  }
  
  void HELibBackend::setKeys(string public_key, string secret_key)
  {
    this->setPublicKey(public_key);
    this->setSecretKey(secret_key);
  }

  string HELibBackend::getCipher()
  {
    string cipher;
    stringstream cipher_stream;

    this->cipher->write(cipher_stream);
    cipher = Util::uuencodeStream(cipher_stream);

    return cipher; 
  }

  void HELibBackend::writeCipherToStream(ostream& stream)
  {
    this->cipher->write(stream);
  }

  void HELibBackend::setCipher(string cipher)
  {
    stringstream cipher_stream;

    if (this->cipher == nullptr) {
      this->cipher = new Ctxt(*this->public_key);
    }

    Util::uudecodeString(cipher, cipher_stream);
    this->cipher->read(cipher_stream);
  }

  void HELibBackend::readCipherFromStream(istream &stream)
  {
    if (this->cipher == nullptr) {
      this->cipher = new Ctxt(*this->public_key);
    }

    this->cipher->read(stream);
  }
      
  // !!!TODO!!!
  void HELibBackend::encrypt(vector<long> values)
  {
    
  }
      
  void HELibBackend::encrypt(long value)
  {
    const EncryptedArray& ea = *(this->public_key->getContext().ea);
    vector<long> values(ea.size());

    // set only first value
    values[0] = value;

    // reset cipher if already set
    if (this->cipher != nullptr) {
      delete(this->cipher);
    }
    this->cipher = new Ctxt(*this->public_key);

    // encrypt the value
    ea.encrypt(*this->cipher, *this->public_key, values);
  }

  // !!!TODO!!!
  vector<long> HELibBackend::decryptValues()
  {
    vector<long> result;

    return result;
  }

  long HELibBackend::decrypt()
  {
    long result;
    const EncryptedArray& ea = *(this->secret_key->getContext().ea);
    vector<long> values(ea.size());

    ea.decrypt(*this->cipher, *this->secret_key, values);

    return values[0];
  }

  // !!!TODO!!!
  void HELibBackend::add(vector<long> values)
  {
    
  }

  void HELibBackend::add(long value)
  {
    Ctxt value_cipher(*this->public_key);
    const EncryptedArray& ea = *(this->public_key->getContext().ea);
    vector<long> values(ea.size());

    // set the first element of the array to value
    values[0] = value;

    // encrypt the values vector
    ea.encrypt(value_cipher, *this->public_key, values);

    this->cipher->addCtxt(value_cipher);
  }

  void HELibBackend::negate()
  {
    throw BackendOperationNotSupported("Negate operation not supported for HELib backend.");
  }

  // !!!TODO!!!
  void HELibBackend::multiply(vector<long> values)
  {

  }

  void HELibBackend::multiply(long value)
  {
    Ctxt value_cipher(*this->public_key);
    const EncryptedArray& ea = *(this->public_key->getContext().ea);
    vector<long> values(ea.size());

    // set the first element of the array to value
    values[0] = value;

    // encrypt the values vector
    ea.encrypt(value_cipher, *this->public_key, values);

    this->cipher->multiplyBy(value_cipher);
  }
}