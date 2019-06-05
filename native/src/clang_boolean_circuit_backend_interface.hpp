#ifndef _HOMOMORPHINE_CLANG_BOOLEAN_CIRCUIT_BACKEND_INTERFACE_H_
#define _HOMOMORPHINE_CLANG_BOOLEAN_CIRCUIT_BACKEND_INTERFACE_H_

#ifdef __cplusplus
extern "C" {
#endif
  #include "clang_types.hpp"

  //! Boolean Circuit backend wrapper that can be used by CLang wrapper in other programming languages (i.e. Golang)
  typedef void* BooleanCircuitBackendWrapper;

  /*!
   * Memory allocation cleanup
   * 
   * \param wrapper backend wrapper
   */
  void FreeBooleanCircuitBackend(BooleanCircuitBackendWrapper wrapper);

  /*!
   * Boolean circuit backend initialization method - initializes all the basic
   * parameters and behavior of a specific backend implementation
   * 
   * \param wrapper backend wrapper
   */
  void InitBooleanCircuitBackend(BooleanCircuitBackendWrapper wrapper);

  /*! 
   * Sets the specific homomorphic algorithm implementation
   * that boolean circuit backend provides
   * 
   * \param wrapper backend wrapper
   * \param algorithm homomorphic encryption algorithm
   */
  void SetBooleanCircuitBackendAlgorithm(BooleanCircuitBackendWrapper wrapper, char* algorithm);
  
  /*!
   * Returns the specific parameter
   * 
   * \param wrapper backend wrapper
   * \param key parameter name
   * \return parameter value
   */
  char* GetBooleanCircuitBackendParam(BooleanCircuitBackendWrapper wrapper, char* key);

  /*!
   * Sets the specific parameter
   * 
   * \param wrapper backend wrapper
   * \param key parameter name
   * \param value parameter value
   */
  void SetBooleanCircuitBackendParam(BooleanCircuitBackendWrapper wrapper, char* key, char* value);

  /*!
   * Generates the public/secret key pair
   * 
   * \param wrapper backend wrapper
   */
  void GenerateBooleanCircuitBackendKeys(BooleanCircuitBackendWrapper wrapper);

  /*!
   * Returns the serialized byte array with public key
   * 
   * \param wrapper backend wrapper
   * \return public key
   */
  char* GetBooleanCircuitBackendPublicKey(BooleanCircuitBackendWrapper wrapper);

  /*!
   * Returns the serialized byte array with secret key
   * 
   * \param wrapper backend wrapper
   * \return secret key
   */
  char* GetBooleanCircuitBackendSecretKey(BooleanCircuitBackendWrapper wrapper);

  /*!
   * Sets the public key using the key in serialized byte array format
   * 
   * \param wrapper backend wrapper
   * \param public_key public key
   */
  void SetBooleanCircuitBackendPublicKey(BooleanCircuitBackendWrapper wrapper, char* public_key);

  /*!
   * Sets the secret key using the key in serialized byte array format
   * 
   * \param wrapper backend wrapper
   * \param secret_key secret key
   */
  void SetBooleanCircuitBackendSecretKey(BooleanCircuitBackendWrapper wrapper, char* secret_key);

  /*!
   * Sets the both public and secret keys using the keys in serialized byte array format
   * 
   * \param wrapper backend wrapper
   * \param public_key public key
   * \param secret_key secret key
   */
  void SetBooleanCircuitBackendKeys(BooleanCircuitBackendWrapper wrapper, char* public_key, char* secret_key);

  /*!
   * Returns the cipher byte array containing encrypted value
   * 
   * \param wrapper backend wrapper
   * \param value value
   * \return encrypted cipher 
   */
  char* BooleanCircuitEncrypt(BooleanCircuitBackendWrapper wrapper, int value);

  /*!
   * Returns the byte array containing encoded value (using public key)
   * 
   * \param wrapper backend wrapper
   * \param value value
   * \return encoded cipher
   */
  char* BooleanCircuitEncode(BooleanCircuitBackendWrapper wrapper, int value);

  /*!
   * Returns a value decrypted from cipher
   * 
   * \param wrapper backend wrapper
   * \param cipher cipher
   * \return decrypted value
   */
  int BooleanCircuitDecrypt(BooleanCircuitBackendWrapper wrapper, char* cipher);

  /*!
   * Perform boolean NOT operation on cipher
   * 
   * \param result stream with the result cipher
   * \param cipher cipher 
   * \return result cipher
   */
  char* BooleanCircuitNOT(BooleanCircuitBackendWrapper wrapper, char* cipher);

  /*!
   * Perform COPY operation on cipher
   * 
   * \param result stream with the result cipher
   * \param cipher cipher with encrypted value
   * \return result cipher
   */
  char* BooleanCircuitCOPY(BooleanCircuitBackendWrapper wrapper, char* cipher);

#ifdef __cplusplus
}
#endif

#endif