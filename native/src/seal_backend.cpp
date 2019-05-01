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

    return uuencodeStream(key_stream);   
  }

  string SealBackend::generateEncodedSecretKey() 
  {
    std::stringstream key_stream;
    SecretKey secret_key = this->keygen->secret_key();

    secret_key.save(key_stream);

    return uuencodeStream(key_stream);
  }

  pair<string, string> SealBackend::generateEncodedKeys() 
  {
    return pair<string, string> (this->generateEncodedPublicKey(), this->generateEncodedSecretKey());
  }

  string SealBackend::encryptValue(string encoded_public_key, int value)
  {
    Ciphertext cypher;
    PublicKey public_key;
    stringstream cypher_stream;
    stringstream key_stream;
    string encrypted_value;
    Plaintext plain_text;

    Encryptor encryptor(this->context, public_key);
    Evaluator evaluator(this->context);
    IntegerEncoder encoder(this->context);

    // uudecode key
    this->uudecodeString(encoded_public_key, key_stream);
    public_key.load(this->context, key_stream);
     
    // encode and encrypt the value
    plain_text = encoder.encode(value);
    encryptor.encrypt(plain_text, cypher);
    cypher.save(cypher_stream);
    encrypted_value = uuencodeStream(cypher_stream);

    return encrypted_value;
  }

  string SealBackend::uuencodeStream(stringstream &key_stream) 
  {
    stringstream uuencoded_stream;
    string key_string = key_stream.str();
    
    typedef 
      insert_linebreaks<         // insert line breaks every 72 characters
        base64_from_binary<    // convert binary values to base64 characters
          transform_width<   // retrieve 6 bit integers from a sequence of 8 bit bytes
            const char *,
            6,
            8
          >
        > 
        ,72
      > 
      base64_text; // compose all the above operations in to a new iterator

    std::copy(
      base64_text(key_string.c_str()),
      base64_text(key_string.c_str() + key_string.size()),
      boost::archive::iterators::ostream_iterator<char>(uuencoded_stream)
    ); 

    return uuencoded_stream.str();
  }

  void SealBackend::uudecodeString(string encoded_key, stringstream &key_stream)
  {
    typedef 
      transform_width< 
        binary_from_base64<
          remove_whitespace<
            const char *
          > 
        >,
        8,
        6 
      > 
      text_base64;

    std::copy(
      text_base64(encoded_key.c_str()),
      text_base64(encoded_key.c_str() + encoded_key.size()),
      boost::archive::iterators::ostream_iterator<char>(key_stream)
    ); 
  }

}