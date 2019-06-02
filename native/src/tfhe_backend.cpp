#include "tfhe_backend.hpp"

namespace homomorphine {
  
  TFHEBackend::~TFHEBackend()
  {
    if (this->cipher != nullptr) {
      delete_gate_bootstrapping_ciphertext_array(this->bits_encrypt, this->cipher);
    }
    
    // secret key contains public one as well...
    if (this->secret_key != nullptr) {
      delete(this->secret_key);
    } 
    else if (this->public_key != nullptr) {
      delete(this->public_key);
    }
  }

  void TFHEBackend::setAlgorithm(string algorithm)
  {
    this->algorithm = TFHEAlgorithm::DEFAULT; // there is only one atm
  }

  void TFHEBackend::init()
  {
    int minimum_lambda;

    // depth of a random vector
    params.count("random_depth") ?
      this->random_depth = stoi(this->params["random_depth"]) :
      this->random_depth = Constants::TFHE_RANDOM_DEPTH;

    // number of bits used for encryption
    params.count("bits_encrypt") ?
      this->bits_encrypt = stoi(this->params["bits_encrypt"]) :
      this->bits_encrypt = Constants::TFHE_BITS_ENCRYPT;

    // minimum lambda
    params.count("minimum_lambda") ?
      minimum_lambda = stoi(this->params["minimum_lambda"]) :
      minimum_lambda = Constants::TFHE_MINIMUM_LAMBDA;

    // bootstrap TFHE
    if (this->context == nullptr) {
      delete(this->context);
    }
    this->context = new_default_gate_bootstrapping_parameters(minimum_lambda);
  }

  void TFHEBackend::generateKeys()  
  {
    vector<uint32_t> seed = this->getSeed(this->random_depth);

    tfhe_random_generator_setSeed(&seed[0], seed.size());

    // secret key contains public one as well...
    if (this->secret_key != nullptr) {
      delete(this->secret_key);
    } 
    else if (this->public_key != nullptr) {
      delete(this->public_key);
    }

    // generate the keys
    this->secret_key = new_random_gate_bootstrapping_secret_keyset(this->context);
    this->public_key = &this->secret_key->cloud;
  }

  string TFHEBackend::getPublicKey()
  {
    stringstream key_stream;
    export_tfheGateBootstrappingCloudKeySet_toStream(key_stream, this->public_key);

    return Util::uuencodeStream(key_stream);    
  }

  string TFHEBackend::getSecretKey()
  {
    stringstream key_stream;
    export_tfheGateBootstrappingSecretKeySet_toStream(key_stream, this->secret_key);

    return Util::uuencodeStream(key_stream);  
  }

  pair<string, string> TFHEBackend::getKeys()
  {
    return pair<string, string> (this->getPublicKey(), this->getSecretKey());
  }

  void TFHEBackend::setPublicKey(string public_key)
  {
    stringstream key_stream;
    Util::uudecodeString(public_key, key_stream);

    this->public_key = new_tfheGateBootstrappingCloudKeySet_fromStream(key_stream);
  }

  void TFHEBackend::setSecretKey(string secret_key)
  {
    stringstream key_stream;
    Util::uudecodeString(secret_key, key_stream);

    this->secret_key = new_tfheGateBootstrappingSecretKeySet_fromStream(key_stream);
  }

  void TFHEBackend::setKeys(string public_key, string secret_key)
  {
    this->setPublicKey(public_key);
    this->setSecretKey(secret_key);
  }

  string TFHEBackend::encrypt(int value)
  {
    stringstream cipher_stream;
    this->cipher = new_gate_bootstrapping_ciphertext_array(this->bits_encrypt, this->context);

    // encrypt all the bits
    for (int i = 0; i < this->bits_encrypt; i++) {
      bootsSymEncrypt(&this->cipher[i], (value>>i)&1, this->secret_key);
    }

    // export cipher to stream
    export_gate_bootstrapping_ciphertext_toStream(cipher_stream, this->cipher, this->context);

    return Util::uuencodeStream(cipher_stream);
  }

  string TFHEBackend::getCipher()
  {
    stringstream cipher_stream;

    // sanity check
    if (this->cipher == nullptr) {
      return "";
    }

    // export cipher to stream
    export_gate_bootstrapping_ciphertext_toStream(cipher_stream, this->cipher, this->context);

    return Util::uuencodeStream(cipher_stream);
  }

  void TFHEBackend::setCipher(string cipher)
  {
    stringstream cipher_stream;

    Util::uudecodeString(cipher, cipher_stream);
    import_gate_bootstrapping_ciphertext_fromStream(cipher_stream, this->cipher, this->context);
  }

  int TFHEBackend::decrypt()
  {
    int result = 0;

    for (int i = 0; i< this->bits_encrypt; i++) {
      int ai = bootsSymDecrypt(&this->cipher[i], this->secret_key);
      result |= (ai<<i);
    }

    return result;
  }

  void TFHEBackend::process(int value, BooleanCircuitOperation operation)
  {

  }

  vector<uint32_t> TFHEBackend::getSeed(int &size) 
  {
    vector<uint32_t> result(size);
    boost::random::mt19937 generator;
    boost::random::uniform_int_distribution<> distribution(0, numeric_limits<int>::max());

    // seed the generator and generate random numbers
    generator.seed(time(0));

    for (int i = 0; i < size; i++) {
      result[i] = distribution(generator);
    }

    return result;
  }
}