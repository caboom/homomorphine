#include "seal_backend.hpp"

namespace homomorphine 
{
  SealBackend::~SealBackend() { 
    delete(encoder);
    delete(keygen);
  }

  void SealBackend::setAlgorithm(string algorithm) 
  {
    this->algorithm = getAlgorithmType(algorithm);
  }

  void SealBackend::setAlgorithm(SealAlgorithmType algorithm) 
  {
    this->algorithm = algorithm;
  }

  SealAlgorithmType SealBackend::getAlgorithmType(string name) 
  {
    boost::algorithm::to_lower(name);

    if (name == "bfv") return SEAL_BFV;
    if (name == "ckks") return SEAL_CKKS;

    return SEAL_UNKNOWN;
  }

  void SealBackend::init() 
  {
    if (this->algorithm == SEAL_BFV) { 
      this->initBFV();
    } 
    else if (this->algorithm == SEAL_CKKS) {
      this->initCKKS();
    } 
    else {
      BOOST_LOG_TRIVIAL(error) << "Unknown backend: " << this->algorithm;
      throw BackendException("Unknown backend");
    }
  }

  void SealBackend::initBFV() 
  {
    uint64_t coeff_modulus;
    int security_level;
    this->encryption_params = new EncryptionParameters(scheme_type::BFV);

    // check if there is poly modulus degree option
    params.count("poly_modulus_degree") ?
      this->encryption_params->set_poly_modulus_degree(stoi(this->params["poly_modulus_degree"])) :
      this->encryption_params->set_poly_modulus_degree(Constants::SEAL_POLY_MODULUS_DEGREE);

    // check if there is coefficient modulus option
    params.count("coeff_modulus") ?
      coeff_modulus = stoull(this->params["coeff_modulus"]) :
      coeff_modulus = Constants::SEAL_COEFF_MODULUS;

    // check if the #bits for encryption had been set
    params.count("security_level") ?
      security_level = stoi(this->params["security_level"]) :
      security_level = Constants::SEAL_SECURITY_LEVEL; 

    // use different functions depending on the security level (128 is default)
    switch (security_level) {
      case 192:
        this->encryption_params->set_coeff_modulus(DefaultParams::coeff_modulus_192(coeff_modulus));
      case 256:
        this->encryption_params->set_coeff_modulus(DefaultParams::coeff_modulus_256(coeff_modulus));
      default:
        this->encryption_params->set_coeff_modulus(DefaultParams::coeff_modulus_128(coeff_modulus));
    }

    // use default recommendation for now
    this->encryption_params->set_plain_modulus(40961);

    this->context = SEALContext::Create(*this->encryption_params);

    this->encoder = new BatchEncoder(context);
    this->keygen = new KeyGenerator(context);
  }

  void SealBackend::initCKKS() 
  {
    this->encryption_params = new EncryptionParameters(scheme_type::CKKS);

    // CKKS needs scale to determine bit-precision of encoding
    params.count("scale") ?
      this->scale = stod(this->params["scale"]):
      this->scale = Constants::SEAL_CKKS_SCALE;

    // check if there is poly modulus degree option
    params.count("poly_modulus_degree") ?
      this->encryption_params->set_poly_modulus_degree(stoi(this->params["poly_modulus_degree"])) :
      this->encryption_params->set_poly_modulus_degree(Constants::SEAL_POLY_MODULUS_DEGREE);

    // check if there is coefficient modulus option
    params.count("coeff_modulus") ?
      this->encryption_params->set_coeff_modulus(DefaultParams::coeff_modulus_128(stoi(this->params["coeff_modulus"]))) :
      this->encryption_params->set_coeff_modulus(DefaultParams::coeff_modulus_128(Constants::SEAL_COEFF_MODULUS));

    this->context = SEALContext::Create(*this->encryption_params);

    //this->encoder = new CKKSEncoder(context);
    this->keygen = new KeyGenerator(context);
  }

  string SealBackend::getPublicKey()
  {
    stringstream key_stream;
    this->public_key.save(key_stream);

    return Util::uuencodeStream(key_stream);   
  }

  string SealBackend::getSecretKey()
  {
    stringstream key_stream;
    this->secret_key.save(key_stream);

    return Util::uuencodeStream(key_stream);   
  }

  pair<string, string> SealBackend::getKeys() 
  {
    return pair<string, string> (this->getPublicKey(), this->getSecretKey());
  }

  PublicKey SealBackend::getSealPublicKey()
  {
    return this->public_key;
  }
  
  SecretKey SealBackend::getSealSecretKey()
  {
    return this->secret_key;
  }

  void SealBackend::setPublicKey(string public_key)
  {
    stringstream key_stream;
    Util::uudecodeString(public_key, key_stream);

    this->public_key.load(this->context, key_stream);
  }
      
  void SealBackend::setSecretKey(string secret_key)
  {
    stringstream key_stream;
    Util::uudecodeString(secret_key, key_stream);
    
    this->secret_key.load(this->context, key_stream); 
  }

  void SealBackend::setKeys(string public_key, string secret_key)
  {
    this->setPublicKey(public_key);
    this->setSecretKey(secret_key);
  }

  pair<PublicKey, SecretKey> SealBackend::getSealKeys()
  {
    return pair<PublicKey, SecretKey> (this->public_key, this->secret_key);
  }

  void SealBackend::setSealPublicKey(PublicKey public_key)
  {
    this->public_key = public_key;
  }
  
  void SealBackend::setSealSecretKey(SecretKey secret_key)
  {
    this->secret_key = secret_key;
  }
  
  void SealBackend::setSealKeys(PublicKey public_key, SecretKey secret_key)
  {
    this->public_key = public_key;
    this->secret_key = secret_key;
  }

  string SealBackend::getCipher()
  {
    string cipher;
    stringstream cipher_stream;

    this->cipher.save(cipher_stream);
    cipher = Util::uuencodeStream(cipher_stream);

    return cipher; 
  }
      
  void SealBackend::setCipher(string cipher)
  {
    stringstream cipher_stream;

    Util::uudecodeString(cipher, cipher_stream);
    this->cipher.load(this->context, cipher_stream);
  }

  void SealBackend::generateKeys() 
  {
    this->public_key = this->keygen->public_key();
    this->secret_key = this->keygen->secret_key();
  }

  string SealBackend::encrypt(vector<int64_t> values)
  {
    stringstream cipher_stream;
    string encrypted_value;
    Plaintext plain_matrix;

    Encryptor encryptor(this->context, this->public_key);
    BatchEncoder encoder(this->context);
     
    // encode and encrypt the value
    plain_matrix = this->encodeWithBFV(values);

    encryptor.encrypt(plain_matrix, this->cipher);
    this->cipher.save(cipher_stream);
    encrypted_value = Util::uuencodeStream(cipher_stream);

    return encrypted_value;
  }

  string SealBackend::encrypt(int64_t value)
  {
    stringstream cipher_stream;
    string encrypted_value;
    Encryptor encryptor(this->context, this->public_key);
    IntegerEncoder encoder(this->context);

    encryptor.encrypt(encoder.encode(value), this->cipher);
    this->cipher.save(cipher_stream);
    encrypted_value = Util::uuencodeStream(cipher_stream);

    return encrypted_value;
  }

  Plaintext SealBackend::encodeWithBFV(vector<int64_t> values)
  {
    Plaintext plain_matrix;
    BatchEncoder batch_encoder(this->context); 
    size_t slot_count = batch_encoder.slot_count();

    batch_encoder.encode(values, plain_matrix);

    return plain_matrix;
  }

  Plaintext SealBackend::encodeWithCKKS(vector<int64_t> values)
  {
    Plaintext plain_matrix;
    CKKSEncoder encoder(this->context);

    // TODO

    return plain_matrix;
  }

  vector<int64_t> SealBackend::decryptValues()
  {
    vector<int64_t> result;
    Plaintext plain_result;
    BatchEncoder batch_encoder(this->context);
    Decryptor decryptor(this->context, this->secret_key);

    decryptor.decrypt(
      this->cipher, 
      plain_result
    );

    batch_encoder.decode(plain_result, result);

    return result;
  }

  int64_t SealBackend::decrypt()
  {
    Plaintext plain_result;
    IntegerEncoder encoder(this->context);
    Decryptor decryptor(this->context, this->secret_key);

    decryptor.decrypt(
      this->cipher, 
      plain_result
    );

    return encoder.decode_int64(plain_result);
  }

  void SealBackend::add(vector<int64_t> values)
  {
    Plaintext plaintext_value;
    Evaluator evaluator(this->context);
    BatchEncoder encoder(this->context);

    encoder.encode(values, plaintext_value);
    evaluator.add_plain_inplace(this->cipher, plaintext_value);
  }

  void SealBackend::add(int64_t value)
  {
    Evaluator evaluator(this->context);
    IntegerEncoder encoder(this->context);
    Encryptor encryptor(this->context, this->public_key);

    Ciphertext encrypted_value;
    Plaintext plaintext_value = encoder.encode(value);
    
    encryptor.encrypt(plaintext_value, encrypted_value);
    evaluator.add_inplace(this->cipher, encrypted_value);
  }

  void SealBackend::negate()
  {
    Evaluator evaluator(this->context);
    evaluator.negate_inplace(this->cipher);
  }
      
  void SealBackend::multiply(vector<int64_t> values)
  {
    Plaintext plaintext_value;
    Ciphertext encrypted_value;
    KeyGenerator keygen(this->context);
    Evaluator evaluator(this->context);
    BatchEncoder encoder(this->context);
    auto relin_keys = keygen.relin_keys(30);

    encoder.encode(values, plaintext_value);
    evaluator.multiply_plain_inplace(this->cipher, plaintext_value);
    evaluator.relinearize_inplace(this->cipher, relin_keys);
  }

  void SealBackend::multiply(int64_t value)
  {
    Evaluator evaluator(this->context);
    IntegerEncoder encoder(this->context);
    Encryptor encryptor(this->context, this->public_key);

    Ciphertext encrypted_value;
    Plaintext plaintext_value = encoder.encode(value);

    encryptor.encrypt(plaintext_value, encrypted_value);
    evaluator.multiply_inplace(this->cipher, encrypted_value);
  }

}