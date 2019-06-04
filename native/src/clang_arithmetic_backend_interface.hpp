#ifndef _HOMOMORPHINE_CLANG_ARITHMETIC_BACKEND_INTERFACE_H_
#define _HOMOMORPHINE_CLANG_ARITHMETIC_BACKEND_INTERFACE_H_

#ifdef __cplusplus
extern "C" {
#endif
  #include "clang_types.hpp"

  //! Arithmetic backend wrapper that can be used by CLang wrapper in other programming languages (i.e. Golang)
  typedef void* ArithmeticBackendWrapper;

  /*!
   * Creates the specific backend using the backend name
   * 
   * \param type backend name
   * \returns backend wrapper
   */
  ArithmeticBackendWrapper CreateArithmeticBackend(char *type);

  /*!
   * Memory allocation cleanup
   * 
   * \param wrapper backend wrapper
   */
  void FreeArithmeticBackend(ArithmeticBackendWrapper wrapper);

  /*!
   * Backend initialization method - initializes all the basic
   * parameters and behavior of a specific arithcmetic backend implementation
   * 
   * \param wrapper backend wrapper
   */
  void InitArithmeticBackend(ArithmeticBackendWrapper wrapper);

  /*! 
   * Sets the specific homomorphic algorithm implementation
   * that arithmetic backend provides
   * 
   * \param wrapper backend wrapper
   * \param algorithm homomorphic encryption algorithm
   */
  void SetArithmeticBackendAlgorithm(ArithmeticBackendWrapper wrapper, char* algorithm);
  
  /*!
   * Returns the specific parameter
   * 
   * \param wrapper backend wrapper
   * \param key parameter name
   * \return parameter value
   */
  char* GetArithmeticBackendParam(ArithmeticBackendWrapper wrapper, char* key);

  /*!
   * Sets the specific parameter
   * 
   * \param wrapper backend wrapper
   * \param key parameter name
   * \param value parameter value
   */
  void SetArithmeticBackendParam(ArithmeticBackendWrapper wrapper, char* key, char* value);

  /*!
   * Generates the public/secret key pair
   * 
   * \param wrapper backend wrapper
   */
  void GenerateArithmeticBackendKeys(ArithmeticBackendWrapper wrapper);

  /*!
   * Returns the UUEncoded public key
   * 
   * \param wrapper backend wrapper
   * \return public key
   */
  char* GetArithmeticBackendPublicKey(ArithmeticBackendWrapper wrapper);

  /*!
   * Returns the UUEncoded secret key
   * 
   * \param wrapper backend wrapper
   * \return secret key
   */
  char* GetArithmeticBackendSecretKey(ArithmeticBackendWrapper wrapper);

  /*!
   * Sets the public key 
   * 
   * \param wrapper backend wrapper
   * \param public_key UUEncoded public key
   */
  void SetArithmeticBackendPublicKey(ArithmeticBackendWrapper wrapper, char* public_key);

  /*!
   * Sets the secret key 
   * 
   * \param wrapper backend wrapper
   * \param secret_key UUEncoded secret key
   */
  void SetArithmeticBackendSecretKey(ArithmeticBackendWrapper wrapper, char* secret_key);

  /*!
   * Sets the both public and secret keys 
   * 
   * \param wrapper backend wrapper
   * \param public_key UUEncoded public key
   * \param secret_key UUEncoded secret key
   */
  void SetArithmeticBackendKeys(ArithmeticBackendWrapper wrapper, char* public_key, char* secret_key);

  /*!
   * Returns the UUEncoded cipher containing ecrypted value, or vector of values
   * 
   * \param wrapper backend wrapper
   * \return UUEncoded cipher
   */
  char* GetArithmeticBackendCipher(ArithmeticBackendWrapper wrapper);

  /*!
   * Sets the UUEncoded cipher containing ecrypted value, or vector of values
   * 
   * \param wrapper backend wrappers
   * \param cipher UUEncoded cipher
   */
  void SetArithmeticBackendCipher(ArithmeticBackendWrapper wrapper, char* cipher);

  /*!
   * Encrypts the single value using the public key
   * 
   * \param wrapper backend wrapper
   * \param value value
   * \return UUEncoded cipher
   */
  void ArithmeticBackendEncrypt(ArithmeticBackendWrapper wrapper, long value);

  /*!
   * Decrypts the single value using the secret key
   * 
   * \param wrapper backend wrapper
   * \return decrypted value
   */
  long ArithmeticBackendDecrypt(ArithmeticBackendWrapper wrapper);

  /*!
   * Adds the value to encrypted value
   * 
   * \param wrapper backend wrapper
   * \param value value
   */
  void ArithmeticBackendAdd(ArithmeticBackendWrapper wrapper, long value);

  /*!
   * Negates a single encrypted value, or a vector of encrypted values
   * 
   * \param wrapper backend wrapper
   */
  void ArithmeticBackendNegate(ArithmeticBackendWrapper wrapper);

  /*!
   * Multiplies the value with the encrypted value
   * 
   * \param wrapper backend wrapper
   * \param value value
   */
  void ArithmeticBackendMultiply(ArithmeticBackendWrapper wrapper, long value);

#ifdef __cplusplus
}
#endif

#endif