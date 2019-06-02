#include "tfhe_backend.hpp"

namespace homomorphine {
  
  TFHEBackend::~TFHEBackend()
  {

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

    // minimum lambda
    params.count("minimum_lambda") ?
      minimum_lambda = stoi(this->params["minimum_lambda"]) :
      minimum_lambda = Constants::TFHE_MINIMUM_LAMBDA;

    // bootstrap TFHE
    this->context = new_default_gate_bootstrapping_parameters(minimum_lambda);
  }

  void TFHEBackend::generateKeys()  
  {
    vector<uint32_t> seed = this->getSeed(this->random_depth);

    tfhe_random_generator_setSeed(&seed[0], seed.size());

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

  string TFHEBackend::getCipher()
  {
    return "";
  }

  void TFHEBackend::setCipher(string cipher)
  {

  }

  void TFHEBackend::process(int value, BooleanCircuitOperation operation)
  {

  }

  vector<uint32_t> TFHEBackend::getSeed(int &size) 
  {
    vector<uint32_t> result(size);
    boost::random::mt19937 generator;
    boost::random::uniform_int_distribution<> distribution(numeric_limits<uint32_t>::min(), numeric_limits<uint32_t>::max());

    // seed the generator and generate random numbers
    generator.seed(time(0));

    for (int i = 0; i < size; i++) {
      result[i] = distribution(generator);
    }

    return result;
  }
}