#ifndef _HOMOMORPHINE_CLANG_BOOLEAN_CIRCUIT_BACKEND_INTERFACE_H_
#define _HOMOMORPHINE_CLANG_BOOLEAN_CIRCUIT_BACKEND_INTERFACE_H_

#ifdef __cplusplus
extern "C" {
#endif
  #include "clang_types.hpp"

  //! Boolean Circuit backend wrapper that can be used by CLang wrapper in other programming languages (i.e. Golang)
  typedef void* BooleanCircuitBackendWrapper;

  /*!
   * Creates the specific boolean circuit backend using the backend name
   * 
   * \param type backend name
   * \returns backend wrapper
   */
  BooleanCircuitBackendWrapper CreateBooleanCircuitBackend(char *type);

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
  Blob GetBooleanCircuitBackendPublicKey(BooleanCircuitBackendWrapper wrapper);

  /*!
   * Returns the serialized byte array with secret key
   * 
   * \param wrapper backend wrapper
   * \return secret key
   */
  Blob GetBooleanCircuitBackendSecretKey(BooleanCircuitBackendWrapper wrapper);

  /*!
   * Sets the public key using the key in serialized byte array format
   * 
   * \param wrapper backend wrapper
   * \param public_key public key
   */
  void SetBooleanCircuitBackendPublicKey(BooleanCircuitBackendWrapper wrapper, Blob public_key);

  /*!
   * Sets the secret key using the key in serialized byte array format
   * 
   * \param wrapper backend wrapper
   * \param secret_key secret key
   */
  void SetBooleanCircuitBackendSecretKey(BooleanCircuitBackendWrapper wrapper, Blob secret_key);

  /*!
   * Sets the both public and secret keys using the keys in serialized byte array format
   * 
   * \param wrapper backend wrapper
   * \param public_key public key
   * \param secret_key secret key
   */
  void SetBooleanCircuitBackendKeys(BooleanCircuitBackendWrapper wrapper, Blob public_key, Blob secret_key);

  /*!
   * Returns the cipher byte array containing encrypted value
   * 
   * \param wrapper backend wrapper
   * \param value value
   * \return encrypted cipher 
   */
  Blob BooleanCircuitEncrypt(BooleanCircuitBackendWrapper wrapper, int value);

  /*!
   * Returns the byte array containing encoded value (using public key)
   * 
   * \param wrapper backend wrapper
   * \param value value
   * \return encoded cipher
   */
  Blob BooleanCircuitEncode(BooleanCircuitBackendWrapper wrapper, int value);

  /*!
   * Returns a value decrypted from cipher
   * 
   * \param wrapper backend wrapper
   * \param cipher cipher
   * \return decrypted value
   */
  int BooleanCircuitDecrypt(BooleanCircuitBackendWrapper wrapper, Blob cipher);

  /*!
   * Perform boolean NOT operation on cipher
   * 
   * \param result stream with the result cipher
   * \param cipher cipher 
   * \return result cipher
   */
  Blob BooleanCircuitNOT(BooleanCircuitBackendWrapper wrapper, Blob cipher);

  /*!
   * Perform COPY operation on cipher
   * 
   * \param result stream with the result cipher
   * \param cipher cipher with encrypted value
   * \return result cipher
   */
  Blob BooleanCircuitCOPY(BooleanCircuitBackendWrapper wrapper, Blob cipher);

  /*!
   * Perform boolean NAND operation on two ciphers
   * 
   * \param stream with the result cipher
   * \param cipher_x first cipher with encrypted value
   * \param cipher_y second cipher with encrypted value
   */
  Blob BooleanCircuitNAND(BooleanCircuitBackendWrapper wrapper, Blob cipher_x, Blob cipher_y);

  /*!
   * Perform boolean OR operation on two ciphers
   * 
   * \param stream with the result cipher
   * \param cipher_x first cipher with encrypted value
   * \param cipher_y second cipher with encrypted value
   */
  Blob BooleanCircuitOR(BooleanCircuitBackendWrapper wrapper, Blob cipher_x, Blob cipher_y);

  /*!
   * Perform boolean AND operation on two ciphers
   * 
   * \param stream with the result cipher
   * \param cipher_x first cipher with encrypted value
   * \param cipher_y second cipher with encrypted value
   */
  Blob BooleanCircuitAND(BooleanCircuitBackendWrapper wrapper, Blob cipher_x, Blob cipher_y);

  /*!
   * Perform boolean XOR operation on two ciphers
   * 
   * \param stream with the result cipher
   * \param cipher_x first cipher with encrypted value
   * \param cipher_y second cipher with encrypted value
   */
  Blob BooleanCircuitXOR(BooleanCircuitBackendWrapper wrapper, Blob cipher_x, Blob cipher_y);

  /*!
   * Perform boolean XNOR operation on two ciphers
   * 
   * \param stream with the result cipher
   * \param cipher_x first cipher with encrypted value
   * \param cipher_y second cipher with encrypted value
   */
  Blob BooleanCircuitXNOR(BooleanCircuitBackendWrapper wrapper, Blob cipher_x, Blob cipher_y);

  /*!
   * Perform boolean NOR operation on two ciphers
   * 
   * \param stream with the result cipher
   * \param cipher_x first cipher with encrypted value
   * \param cipher_y second cipher with encrypted value
   */
  Blob BooleanCircuitNOR(BooleanCircuitBackendWrapper wrapper, Blob cipher_x, Blob cipher_y);

  /*!
   * Perform boolean MUX operation on two ciphers
   * 
   * \param stream with the result cipher
   * \param cipher_x first cipher with encrypted value
   * \param cipher_y second cipher with encrypted value
   */
  Blob BooleanCircuitMUX(BooleanCircuitBackendWrapper wrapper, Blob cipher_x, Blob cipher_y, Blob cipher_z);

#ifdef __cplusplus
}
#endif

#endif