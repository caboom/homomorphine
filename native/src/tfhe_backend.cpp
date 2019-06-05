#include "tfhe_backend.hpp"

namespace homomorphine {
  
  TFHEBackend::~TFHEBackend()
  {
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

  void TFHEBackend::writePublicKeyToStream(ostream& stream)
  {
    export_tfheGateBootstrappingCloudKeySet_toStream(stream, this->public_key);
  }

  string TFHEBackend::getSecretKey()
  {
    stringstream key_stream;
    export_tfheGateBootstrappingSecretKeySet_toStream(key_stream, this->secret_key);

    return Util::uuencodeStream(key_stream);  
  }

  void TFHEBackend::writeSecretKeyToStream(ostream& stream)
  {
    export_tfheGateBootstrappingSecretKeySet_toStream(stream, this->secret_key);
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

  void TFHEBackend::readPublicKeyFromStream(istream &stream)
  {
    this->public_key = new_tfheGateBootstrappingCloudKeySet_fromStream(stream);
  }

  void TFHEBackend::setSecretKey(string secret_key)
  {
    stringstream key_stream;
    Util::uudecodeString(secret_key, key_stream);

    this->secret_key = new_tfheGateBootstrappingSecretKeySet_fromStream(key_stream);
  }

  void TFHEBackend::readSecretKeyFromStream(istream &stream)
  {
    this->secret_key = new_tfheGateBootstrappingSecretKeySet_fromStream(stream);
  }

  void TFHEBackend::setKeys(string public_key, string secret_key)
  {
    this->setPublicKey(public_key);
    this->setSecretKey(secret_key);
  }

  string TFHEBackend::encryptToString(int value)
  {
    string result;
    stringstream stream;
    LweSample* cipher = new_gate_bootstrapping_ciphertext_array(this->bits_encrypt, this->context);

    // encrypt all the bits
    for (int i = 0; i < this->bits_encrypt; i++) {
      bootsSymEncrypt(&cipher[i], (value>>i)&1, this->secret_key);
    }
    
    // export cipher to stream and encode the stream
    for (int i = 0; i < this->bits_encrypt; i++) {
      export_gate_bootstrapping_ciphertext_toStream(stream, &cipher[i], this->context);
    }
    result = Util::uuencodeStream(stream);

    // cleanup
    delete_gate_bootstrapping_ciphertext_array(this->bits_encrypt, cipher);

    return result;
  }

  void TFHEBackend::encryptToStream(int value, ostream& stream) 
  {
    LweSample* cipher = new_gate_bootstrapping_ciphertext_array(this->bits_encrypt, this->context);

    // encrypt all the bits
    for (int i = 0; i < this->bits_encrypt; i++) {
      bootsSymEncrypt(&cipher[i], (value>>i)&1, this->secret_key);
    }
    
    // export cipher to stream and encode the stream
    for (int i = 0; i < this->bits_encrypt; i++) {
      export_gate_bootstrapping_ciphertext_toStream(stream, &cipher[i], this->context);
    }

    // cleanup
    delete_gate_bootstrapping_ciphertext_array(this->bits_encrypt, cipher);
  }
  
  string TFHEBackend::encodeToString(int value)
  {
    string result;
    stringstream stream;
    LweSample* cipher = new_gate_bootstrapping_ciphertext_array(this->bits_encrypt, this->context);

    for (int i = 0; i < this->bits_encrypt; i++) {
      bootsCONSTANT(&cipher[i], (64>>i)&1, this->public_key);
    }

    // export cipher to stream and encode the stream
    for (int i = 0; i < this->bits_encrypt; i++) {
      export_gate_bootstrapping_ciphertext_toStream(stream, &cipher[i], this->public_key->params);
    }
    result = Util::uuencodeStream(stream);

    // cleanup
    delete_gate_bootstrapping_ciphertext_array(this->bits_encrypt, cipher);

    return result;
  }

  void TFHEBackend::encodeToStream(int value, ostream& stream)
  {
    LweSample* cipher = new_gate_bootstrapping_ciphertext_array(this->bits_encrypt, this->public_key->params);

    for (int i = 0; i < this->bits_encrypt; i++) {
      bootsCONSTANT(&cipher[i], (value>>i)&1, this->public_key);
    }

    // export cipher to stream and encode the stream
    for (int i = 0; i < this->bits_encrypt; i++) {
      export_gate_bootstrapping_ciphertext_toStream(stream, &cipher[i], this->public_key->params);
    }

    // cleanup
    delete_gate_bootstrapping_ciphertext_array(this->bits_encrypt, cipher);
  }

  int TFHEBackend::decryptFromStream(istream& stream)
  {
    int result = 0;
    LweSample* cipher = new_gate_bootstrapping_ciphertext_array(this->bits_encrypt, this->context);

    // import cipher from stream
    for (int i = 0; i< this->bits_encrypt; i++) {
      import_gate_bootstrapping_ciphertext_fromStream(stream, &cipher[i], this->context);
    }

    // decrypt cipher
    for (int i = 0; i< this->bits_encrypt; i++) {
      int ai = bootsSymDecrypt(&cipher[i], this->secret_key);
      result |= (ai<<i);
    }

    // cleanup
    delete_gate_bootstrapping_ciphertext_array(this->bits_encrypt, cipher);

    return result;
  }

  void TFHEBackend::NOT(ostream& result, istream& cipher)
  {
    this->process(result, cipher, BooleanCircuitOperation::NOT);
  }

  void TFHEBackend::COPY(ostream& result, istream& cipher)
  {
    this->process(result, cipher, BooleanCircuitOperation::COPY);
  }

  void TFHEBackend::NAND(ostream& result, istream& cipher_x, istream& cipher_y)
  {
    this->process(result, cipher_x, cipher_y, BooleanCircuitOperation::NAND);
  }

  void TFHEBackend::OR(ostream& result, istream& cipher_x, istream& cipher_y)
  {
    this->process(result, cipher_x, cipher_y, BooleanCircuitOperation::OR);
  }

  void TFHEBackend::AND(ostream& result, istream& cipher_x, istream& cipher_y)
  {
    this->process(result, cipher_x, cipher_y, BooleanCircuitOperation::AND);
  }

  void TFHEBackend::XOR(ostream& result, istream& cipher_x, istream& cipher_y)
  {
    this->process(result, cipher_x, cipher_y, BooleanCircuitOperation::XOR);
  }

  void TFHEBackend::OR(ostream& result, istream& cipher_x, istream& cipher_y)
  {
    this->process(result, cipher_x, cipher_y, BooleanCircuitOperation::OR);
  }

  void TFHEBackend::XNOR(ostream& result, istream& cipher_x, istream& cipher_y)
  {
    this->process(result, cipher_x, cipher_y, BooleanCircuitOperation::XNOR);
  }

  void TFHEBackend::NOR(ostream& result, istream& cipher_x, istream& cipher_y)
  {
    this->process(result, cipher_x, cipher_y, BooleanCircuitOperation::NOR);
  }

  void TFHEBackend::MUX(ostream& result, istream& cipher_x, istream& cipher_y, istream& cipher_z)
  {
    this->process(result, cipher_x, cipher_y, cipher_z, BooleanCircuitOperation::MUX);
  }

  //
  // PRIVATE INTERFACE
  //

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

  LweSample* TFHEBackend::readCipherFromStream(istream &stream) 
  {
    LweSample* cipher = new_gate_bootstrapping_ciphertext_array(this->bits_encrypt, this->public_key->params);

    for (int i = 0; i< this->bits_encrypt; i++) {
      import_gate_bootstrapping_ciphertext_fromStream(stream, &cipher[i], this->context);
    }

    return cipher;
  }

  void TFHEBackend::writeCipherToStream(LweSample* cipher, ostream& stream)
  {
    if (cipher != nullptr) {
      for (int i = 0; i < this->bits_encrypt; i++) {
        export_gate_bootstrapping_ciphertext_toStream(stream, &cipher[i], this->context);
      }
    }
  }

  void TFHEBackend::process(ostream& result, istream& cipher_x, BooleanCircuitOperation operation)
  {
    LweSample* x = this->readCipherFromStream(cipher_x);
    LweSample* output = new_gate_bootstrapping_ciphertext_array(this->bits_encrypt, this->public_key->params);

    switch(operation)
    {
      case BooleanCircuitOperation::NOT:
        for (int i = 0; i < this->bits_encrypt; i++) { bootsNOT(&output[i], &x[i], this->public_key); }
        break;
      case BooleanCircuitOperation::COPY:
        for (int i = 0; i < this->bits_encrypt; i++) { bootsCOPY(&output[i], &x[i], this->public_key); }
        break;
      // if the operation is not matched, it's due to wrong number of 
      // argumens for that operation in that case, cleanup and throw an exception
      default:
        delete_gate_bootstrapping_ciphertext_array(this->bits_encrypt, x);

        throw BackendOperationNotSupported("Wrong number of arguments");
        break;
    }

    // write result cipher to result stream
    this->writeCipherToStream(output, result);

    // cleanup
    delete_gate_bootstrapping_ciphertext_array(this->bits_encrypt, x);
  }

  void TFHEBackend::process(ostream& result, istream& cipher_x, istream& cipher_y, BooleanCircuitOperation operation)
  {
    LweSample* x = this->readCipherFromStream(cipher_x);
    LweSample* y = this->readCipherFromStream(cipher_y);
    LweSample* output = new_gate_bootstrapping_ciphertext_array(this->bits_encrypt, this->public_key->params);

    switch(operation)
    {
      case BooleanCircuitOperation::NAND:
        for (int i = 0; i < this->bits_encrypt; i++) { bootsNAND(&output[i], &x[i], &y[i], this->public_key); }
        break;
      case BooleanCircuitOperation::OR:
        for (int i = 0; i < this->bits_encrypt; i++) { bootsOR(&output[i], &x[i], &y[i], this->public_key); }
        break; 
      case BooleanCircuitOperation::AND:
        for (int i = 0; i < this->bits_encrypt; i++) { bootsAND(&output[i], &x[i], &y[i], this->public_key); }
        break; 
      case BooleanCircuitOperation::XOR:
        for (int i = 0; i < this->bits_encrypt; i++) { bootsXOR(&output[i], &x[i], &y[i], this->public_key); }
        break; 
      case BooleanCircuitOperation::XNOR:
        for (int i = 0; i < this->bits_encrypt; i++) { bootsXNOR(&output[i], &x[i], &y[i], this->public_key); }
        break; 
      case BooleanCircuitOperation::NOR:
        for (int i = 0; i < this->bits_encrypt; i++) { bootsNOR(&output[i], &x[i], &y[i], this->public_key); }
        break; 
      // if the operation is not matched, it's due to wrong number of 
      // argumens for that operation in that case, cleanup and throw an exception
      default:
        delete_gate_bootstrapping_ciphertext_array(this->bits_encrypt, x);
        delete_gate_bootstrapping_ciphertext_array(this->bits_encrypt, y);

        throw BackendOperationNotSupported("Wrong number of arguments");
        break;
    }

    // write result cipher to result stream
    this->writeCipherToStream(output, result);

    // cleanup
    delete_gate_bootstrapping_ciphertext_array(this->bits_encrypt, x);
    delete_gate_bootstrapping_ciphertext_array(this->bits_encrypt, y);
  }

  void TFHEBackend::process(ostream& result, istream& cipher_x, istream& cipher_y, istream& cipher_z, BooleanCircuitOperation operation)
  {
    LweSample* x = this->readCipherFromStream(cipher_x);
    LweSample* y = this->readCipherFromStream(cipher_y);
    LweSample* z = this->readCipherFromStream(cipher_z);
    LweSample* output = new_gate_bootstrapping_ciphertext_array(this->bits_encrypt, this->public_key->params);

    switch(operation)
    {
      case BooleanCircuitOperation::MUX:
        for (int i = 0; i < this->bits_encrypt; i++) { bootsMUX(&output[i], &x[i], &y[i], &z[i], this->public_key); }
        break;
      // if the operation is not matched, it's due to wrong number of 
      // argumens for that operation in that case, cleanup and throw an exception
      default:
        delete_gate_bootstrapping_ciphertext_array(this->bits_encrypt, x);
        delete_gate_bootstrapping_ciphertext_array(this->bits_encrypt, y);
        delete_gate_bootstrapping_ciphertext_array(this->bits_encrypt, z);

        throw BackendOperationNotSupported("Wrong number of arguments");
        break;
    }

    // write result cipher to result stream
    this->writeCipherToStream(output, result);

    // cleanup
    delete_gate_bootstrapping_ciphertext_array(this->bits_encrypt, x);
    delete_gate_bootstrapping_ciphertext_array(this->bits_encrypt, y);
    delete_gate_bootstrapping_ciphertext_array(this->bits_encrypt, z);
  }
}