#include "seal_backend.hpp"

namespace homomorphine 
{
  SealBackend::~SealBackend() 
  { 
    if (this->keygen != nullptr) {
      delete(this->keygen);
    }
    if (this->encryption_params != nullptr) {
      delete(this->encryption_params);
    }
  }

  void SealBackend::setAlgorithm(string algorithm) 
  {
    this->algorithm = getAlgorithmType(algorithm);
  }

  void SealBackend::setAlgorithm(SealAlgorithm algorithm) 
  {
    this->algorithm = algorithm;
  }

  SealAlgorithm SealBackend::getAlgorithmType(string name) 
  {
    boost::algorithm::to_lower(name);

    if (name == "bfv") return SealAlgorithm::BFV;
    if (name == "ckks") return SealAlgorithm::CKKS;

    return SealAlgorithm::UNKNOWN;
  }

  void SealBackend::init() 
  {
    if (this->algorithm == SealAlgorithm::BFV) { 
      this->initBFV();
    } 
    else if (this->algorithm == SealAlgorithm::CKKS) {
      this->initCKKS();
    } 
    else {
      throw BackendException("Unknown backend");
    }
  }

  void SealBackend::initBFV() 
  {
    uint64_t coeff_modulus;
    int security_level;

    if (this->encryption_params != nullptr) {
      delete(this->encryption_params);
    }
    this->encryption_params = new EncryptionParameters(scheme_type::BFV);

    // check if there is poly modulus degree option
    params.count("poly_modulus_degree") ?
      this->encryption_params->set_poly_modulus_degree(stoi(this->params["poly_modulus_degree"])) :
      this->encryption_params->set_poly_modulus_degree(Constants::SEAL_POLY_MODULUS_DEGREE_BFV);

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

    if(this->keygen != nullptr) {
      delete(this->keygen);
    }
    this->keygen = new KeyGenerator(context);
  }

  void SealBackend::initCKKS() 
  {
    if (this->encryption_params != nullptr) {
      delete(this->encryption_params);
    }
    this->encryption_params = new EncryptionParameters(scheme_type::CKKS);

    // CKKS needs scale to determine bit-precision of encoding
    params.count("scale") ?
      this->scale = stod(this->params["scale"]):
      this->scale = Constants::SEAL_CKKS_SCALE;

    // check if there is poly modulus degree option
    params.count("poly_modulus_degree") ?
      this->encryption_params->set_poly_modulus_degree(stoi(this->params["poly_modulus_degree"])) :
      this->encryption_params->set_poly_modulus_degree(Constants::SEAL_POLY_MODULUS_DEGREE_CKKS);

    // check if there is coefficient modulus option
    params.count("coeff_modulus") ?
      this->encryption_params->set_coeff_modulus(DefaultParams::coeff_modulus_128(stoi(this->params["coeff_modulus"]))) :
      this->encryption_params->set_coeff_modulus(DefaultParams::coeff_modulus_128(Constants::SEAL_COEFF_MODULUS));

    this->context = SEALContext::Create(*this->encryption_params);

    if (this->keygen != nullptr) {
      delete(this->keygen);
    }
    this->keygen = new KeyGenerator(context);
  }

  string SealBackend::getPublicKey()
  {
    stringstream key_stream;
    this->public_key.save(key_stream);

    return Util::uuencodeStream(key_stream);   
  }

  void SealBackend::writePublicKeyToStream(ostream& stream)
  {
    this->public_key.save(stream);
  }

  string SealBackend::getSecretKey()
  {
    stringstream key_stream;
    this->secret_key.save(key_stream);

    return Util::uuencodeStream(key_stream);   
  }

  void SealBackend::writeSecretKeyToStream(ostream& stream)
  {
    this->secret_key.save(stream);
  }

  pair<string, string> SealBackend::getKeys() 
  {
    return pair<string, string> (this->getPublicKey(), this->getSecretKey());
  }

  void SealBackend::setPublicKey(string public_key)
  {
    stringstream key_stream;
    Util::uudecodeString(public_key, key_stream);

    this->public_key.load(this->context, key_stream);
  }

  void SealBackend::readPublicKeyFromStream(istream &stream)
  {
    this->public_key.load(this->context, stream);
  }
      
  void SealBackend::setSecretKey(string secret_key)
  {
    stringstream key_stream;
    Util::uudecodeString(secret_key, key_stream);
    
    this->secret_key.load(this->context, key_stream); 
  }

  void SealBackend::readSecretKeyFromStream(istream &stream)
  {
    this->secret_key.load(this->context, stream);
  }

  void SealBackend::setKeys(string public_key, string secret_key)
  {
    this->setPublicKey(public_key);
    this->setSecretKey(secret_key);
  }

  string SealBackend::getCipher()
  {
    string cipher;
    stringstream cipher_stream;

    this->cipher.save(cipher_stream);
    cipher = Util::uuencodeStream(cipher_stream);

    return cipher; 
  }

  void SealBackend::writeCipherToStream(ostream& stream)
  {
    this->cipher.save(stream);
  }
      
  void SealBackend::setCipher(string cipher)
  {
    stringstream cipher_stream;

    Util::uudecodeString(cipher, cipher_stream);
    this->cipher.load(this->context, cipher_stream);
  }

  void SealBackend::readCipherFromStream(istream &stream)
  {
    this->cipher.load(this->context, stream);
  }

  void SealBackend::generateKeys() 
  {
    this->public_key = this->keygen->public_key();
    this->secret_key = this->keygen->secret_key();
    this->relin_keys = this->keygen->relin_keys(DefaultParams::dbc_max());
  }

  void SealBackend::encrypt(vector<long> values)
  {
    Plaintext plain_matrix;
    Encryptor encryptor(this->context, this->public_key);
     
     // encode with proper encode (BFV is default)
    if (this->algorithm == SealAlgorithm::CKKS) {
      encryptor.encrypt(this->encodeWithCKKS(values), this->cipher);
    }
    else {
      encryptor.encrypt(this->encodeWithBFV(values), this->cipher);
    }
  }

  void SealBackend::encrypt(long value)
  {
    Encryptor encryptor(this->context, this->public_key);

    // encode with proper encode (BFV is default)
    if (this->algorithm == SealAlgorithm::CKKS) {
      encryptor.encrypt(this->encodeWithCKKS(value), this->cipher);
    }
    else {
      encryptor.encrypt(this->encodeWithBFV(value), this->cipher);
    }
  }

  Plaintext SealBackend::encodeWithBFV(vector<long> values)
  {
    Plaintext plain_matrix;
    BatchEncoder batch_encoder(this->context); 
    size_t slot_count = batch_encoder.slot_count();
    vector<int64_t> int64_values(begin(values), end(values));

    batch_encoder.encode(int64_values, plain_matrix);

    return plain_matrix;
  }

  Plaintext SealBackend::encodeWithBFV(long value)
  {
    IntegerEncoder encoder(this->context);
    return encoder.encode((int64_t)value);
  }

  Plaintext SealBackend::encodeWithCKKS(vector<long> values)
  {
    Plaintext plain_matrix;
    CKKSEncoder encoder(this->context);
    vector<double> double_values(begin(values), end(values));

    encoder.encode(double_values, this->scale, plain_matrix);

    return plain_matrix;
  }

  Plaintext SealBackend::encodeWithCKKS(long value)
  {
    Plaintext plain_matrix;
    CKKSEncoder encoder(this->context);

    encoder.encode((double)value, this->scale, plain_matrix);

    return plain_matrix;
  }

  long SealBackend::decrypt()
  {
    long result;
    Plaintext plain_result;
    Decryptor decryptor(this->context, this->secret_key);

    decryptor.decrypt(
      this->cipher, 
      plain_result
    );

    // decode with either CKKS or BFV Integer decoder
    if (this->algorithm == SealAlgorithm::CKKS) {
      result = this->decodeWithCKKS(plain_result);
    }
    else {
      result = this->decodeWithBFV(plain_result); 
    }

    return result;
  }

  vector<long> SealBackend::decryptValues()
  {
    vector<long> result;
    Plaintext plain_result;
    Decryptor decryptor(this->context, this->secret_key);

    decryptor.decrypt(
      this->cipher, 
      plain_result
    );

    // decode with either CKKS or BFV Integer decoder
    if (this->algorithm == SealAlgorithm::CKKS) {
      result = this->decodeValuesWithCKKS(plain_result);
    }
    else {
      result = this->decodeValuesWithBFV(plain_result); 
    }

    return result;
  }

  long SealBackend::decodeWithBFV(Plaintext plain_result) 
  {
    IntegerEncoder encoder(this->context);
    return encoder.decode_int64(plain_result);
  }

  vector<long> SealBackend::decodeValuesWithBFV(Plaintext plain_result) 
  {
    vector<int64_t> result;
    BatchEncoder batch_encoder(this->context);
    
    batch_encoder.decode(plain_result, result);
    vector<long> long_result(begin(result), end(result));
    result.clear();

    return long_result;
  }

  long SealBackend::decodeWithCKKS(Plaintext plain_result) {
    vector<double> results;
    CKKSEncoder encoder(this->context);

    encoder.decode(plain_result, results);

    return lround(results[0]);
  }

  vector<long> SealBackend::decodeValuesWithCKKS(Plaintext plain_result) {
    vector<double> results;
    vector<long> results_l;
    CKKSEncoder encoder(this->context);

    encoder.decode(plain_result, results);

    // cast vector, but with rounding
    results_l.reserve(results.size());
    for (double value : results) { 
      results_l.push_back((long)round(value));
    }
    results.clear();

    return results_l;
  }

  void SealBackend::add(vector<long> values)
  {
    Plaintext plaintext_value;
    Ciphertext encrypted_value;
    Evaluator evaluator(this->context);
    Encryptor encryptor(this->context, this->public_key);
   
    // encode either with CKKS or BFV
    if (this->algorithm == SealAlgorithm::CKKS) {
      plaintext_value = this->encodeWithCKKS(values);
    }
    else {
      plaintext_value = this->encodeWithBFV(values);
    } 

    encryptor.encrypt(plaintext_value, encrypted_value);
    evaluator.add_inplace(this->cipher, encrypted_value);
  }

  void SealBackend::add(long value)
  {
    Plaintext plaintext_value;
    Ciphertext encrypted_value;
    Evaluator evaluator(this->context);
    Encryptor encryptor(this->context, this->public_key);

    // encode either with CKKS or BFV
    if (this->algorithm == SealAlgorithm::CKKS) {
      plaintext_value = this->encodeWithCKKS(value);
    }
    else {
      plaintext_value = this->encodeWithBFV(value);
    } 
    
    encryptor.encrypt(plaintext_value, encrypted_value);
    evaluator.add_inplace(this->cipher, encrypted_value);
  }

  void SealBackend::negate()
  {
    Evaluator evaluator(this->context);
    evaluator.negate_inplace(this->cipher);
  }
      
  void SealBackend::multiply(vector<long> values)
  {
    Plaintext plaintext_value;
    Ciphertext encrypted_value;
    KeyGenerator keygen(this->context);
    Evaluator evaluator(this->context);
    Encryptor encryptor(this->context, this->public_key);
    auto relin_keys = keygen.relin_keys(30);
    
    // encode either with CKKS or BFV
    if (this->algorithm == SealAlgorithm::CKKS) {
      plaintext_value = this->encodeWithCKKS(values);
    }
    else {
      plaintext_value = this->encodeWithBFV(values);
    } 

    encryptor.encrypt(plaintext_value, encrypted_value);
    evaluator.multiply_inplace(this->cipher, encrypted_value);
    evaluator.relinearize_inplace(this->cipher, relin_keys);
  }

  void SealBackend::multiply(long value)
  {
    Plaintext plaintext_value;
    Ciphertext encrypted_value;
    Evaluator evaluator(this->context);
    Encryptor encryptor(this->context, this->public_key);

    // encode either with CKKS or BFV
    if (this->algorithm == SealAlgorithm::CKKS) {
      plaintext_value = this->encodeWithCKKS(value);
    }
    else {
      plaintext_value = this->encodeWithBFV(value);
    } 

    encryptor.encrypt(plaintext_value, encrypted_value);
    evaluator.multiply_inplace(this->cipher, encrypted_value);
  }

}