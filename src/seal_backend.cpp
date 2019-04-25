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
      throw BackendException("Unknown backend: ");
    }
  }

  void SealBackend::initBFV() 
  {
    this->encryption_params = new EncryptionParameters(scheme_type::BFV);

    // check if there is poly modulus degree option
    params.count("poly_modulus_degree") ?
      this->encryption_params->set_poly_modulus_degree(stoi(this->params["poly_modulus_degree"])) :
      this->encryption_params->set_poly_modulus_degree(2048);

    // check if there is coefficient modulus option
    params.count("coeff_modulus") ?
      this->encryption_params->set_coeff_modulus(DefaultParams::coeff_modulus_128(stoi(this->params["coeff_modulus"]))) :
      this->encryption_params->set_coeff_modulus(DefaultParams::coeff_modulus_128(2048));

    // use default recommendation for now
    this->encryption_params->set_plain_modulus(1 << 8);

    this->context = SEALContext::Create(*this->encryption_params);

    this->encoder = new IntegerEncoder(context);
    this->keygen = new KeyGenerator(context);
  }

  PublicKey SealBackend::generatePublicKey() 
  {
    return this->keygen->public_key();
  }

  SecretKey SealBackend::generateSecretKey() 
  {
    return this->keygen->secret_key();
  } 

  pair <PublicKey, SecretKey> SealBackend::generatePublicAndSecretKey() 
  {
    return pair<PublicKey, SecretKey> (this->generatePublicKey(), this->generateSecretKey());
  }

}