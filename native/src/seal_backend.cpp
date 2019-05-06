#include "seal_backend.hpp"

namespace homomorphine 
{
  SealBackend::~SealBackend() { }

  void SealBackend::setAlgorithm(string algorithm) 
  {
    this->type = getAlgorithmType(algorithm);
  }

  void SealBackend::setAlgorithm(SealAlgorithmType algorithm) 
  {
    this->type = algorithm;
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
    if (this->type == SEAL_BFV) { 
      this->initBFV();
    } else {
      BOOST_LOG_TRIVIAL(error) << "Unknown backend: " << this->type;
      throw BackendException("Unknown backend");
    }
  }

  void SealBackend::initBFV() 
  {
    this->encryption_params = new EncryptionParameters(scheme_type::BFV);

    // check if there is poly modulus degree option
    params.count("poly_modulus_degree") ?
      this->encryption_params->set_poly_modulus_degree(stoi(this->params["poly_modulus_degree"])) :
      this->encryption_params->set_poly_modulus_degree(Constants::SEAL_POLY_MODULUS_DEGREE);

    // check if there is coefficient modulus option
    params.count("coeff_modulus") ?
      this->encryption_params->set_coeff_modulus(DefaultParams::coeff_modulus_128(stoi(this->params["coeff_modulus"]))) :
      this->encryption_params->set_coeff_modulus(DefaultParams::coeff_modulus_128(Constants::SEAL_COEFF_MODULUS));

    // use default recommendation for now
    this->encryption_params->set_plain_modulus(1 << 8);

    this->context = SEALContext::Create(*this->encryption_params);

    this->encoder = new IntegerEncoder(context);
    this->keygen = new KeyGenerator(context);
  }

  PublicKey SealBackend::getPublicKey()
  {
    return this->public_key;
  }
  
  SecretKey SealBackend::getSecretKey()
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

  pair<PublicKey, SecretKey> SealBackend::getKeys()
  {
    return pair<PublicKey, SecretKey> (this->public_key, this->secret_key);
  }

  void SealBackend::setPublicKey(PublicKey public_key)
  {
    this->public_key = public_key;
  }
  
  void SealBackend::setSecretKey(SecretKey secret_key)
  {
    this->secret_key = secret_key;
  }
  
  void SealBackend::setKeys(PublicKey public_key, SecretKey secret_key)
  {
    this->public_key = public_key;
    this->secret_key = secret_key;
  }

  string SealBackend::getEncodedCipher()
  {
    string encoded_cipher;
    stringstream cipher_stream;

    this->cipher.save(cipher_stream);
    encoded_cipher = Util::uuencodeStream(cipher_stream);

    return encoded_cipher; 
  }
      
  void SealBackend::setEncodedCipher(string encoded_cipher)
  {
    stringstream cipher_stream;

    Util::uudecodeString(encoded_cipher, cipher_stream);
    this->cipher.save(cipher_stream);
  }

  PublicKey SealBackend::generatePublicKey() 
  {
    this->public_key = this->keygen->public_key();

    return this->public_key;
  }

  SecretKey SealBackend::generateSecretKey() 
  {
    this->secret_key = this->keygen->secret_key();

    return this->secret_key;
  } 

  pair<PublicKey, SecretKey> SealBackend::generateKeys() 
  {
    this->public_key = this->keygen->public_key(); 
    this->secret_key = this->keygen->secret_key();

    return pair<PublicKey, SecretKey> (this->public_key, this->secret_key);
  }

  string SealBackend::generateEncodedPublicKey() 
  {
    std::stringstream key_stream;
    PublicKey public_key = this->keygen->public_key();

    public_key.save(key_stream);

    return Util::uuencodeStream(key_stream);   
  }

  string SealBackend::generateEncodedSecretKey() 
  {
    std::stringstream key_stream;
    SecretKey secret_key = this->keygen->secret_key();

    secret_key.save(key_stream);

    return Util::uuencodeStream(key_stream);
  }

  pair<string, string> SealBackend::generateEncodedKeys() 
  {
    return pair<string, string> (this->generateEncodedPublicKey(), this->generateEncodedSecretKey());
  }

  string SealBackend::encryptValue(int value)
  {
    stringstream cipher_stream;
    string encrypted_value;
    Plaintext plain_text;

    Encryptor encryptor(this->context, this->public_key);
    Evaluator evaluator(this->context);
    IntegerEncoder encoder(this->context);
     
    // encode and encrypt the value
    plain_text = encoder.encode(value);
    encryptor.encrypt(plain_text, this->cipher);
    this->cipher.save(cipher_stream);
    encrypted_value = Util::uuencodeStream(cipher_stream);

    return encrypted_value;
  }

  int SealBackend::decrypt()
  {
    Plaintext plain_result;
    IntegerEncoder encoder(this->context);
    Decryptor decryptor(this->context, this->secret_key);

    decryptor.decrypt(this->cipher, plain_result);

    return encoder.decode_int32(plain_result);
  }

  void SealBackend::add(int value)
  {
    Evaluator evaluator(this->context);
    IntegerEncoder encoder(this->context);
    Encryptor encryptor(this->context, this->public_key);
    Plaintext plaintext_value = encoder.encode(value);
    Ciphertext encrypted_value;

    encryptor.encrypt(plaintext_value, encrypted_value);

    evaluator.add_inplace(this->cipher, encrypted_value);
  }

  void SealBackend::negate()
  {
    Evaluator evaluator(this->context);
    evaluator.negate_inplace(this->cipher);
  }
      
  void SealBackend::multiply(int value)
  {
    Evaluator evaluator(this->context);
    IntegerEncoder encoder(this->context);
    Encryptor encryptor(this->context, this->public_key);
    Plaintext plaintext_value = encoder.encode(value);
    Ciphertext encrypted_value;

    encryptor.encrypt(plaintext_value, encrypted_value);

    evaluator.multiply_inplace(this->cipher, encrypted_value);
  }

}