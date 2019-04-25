#include "seal_backend.hpp"

namespace Homomorphine 
{
  SealBackend::~SealBackend() { }

  void SealBackend::setAlgorithm(string algorithm) {
    this->type = getAlgorithmType(algorithm);
  }

  SealAlgorithmType SealBackend::getAlgorithmType(string name) {
    boost::algorithm::to_lower(name);

    if (name == "bfv") return SEAL_BFV;
    if (name == "ckks") return SEAL_CKKS;

    return SEAL_UNKNOWN;
  }

  void SealBackend::init() {
    if (this->type == SEAL_BFV) { 
      this->initBFV();
    } else {
      throw BackendException("Unknown backend: ");
    }
  }

  void SealBackend::initBFV() {
    this->encryption_params = new EncryptionParameters(scheme_type::BFV);

    if (params.count("poly_modulus_degree")) {
      this->encryption_params->set_poly_modulus_degree(stoi(this->params["poly_modulus_degree"]));
    } else {
      this->encryption_params->set_poly_modulus_degree(2048);
    }
  }

}