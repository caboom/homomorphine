#ifdef __cplusplus
extern "C" {
#endif
  #include "clang_types.hpp"

  //! Backend wrapper that can be used by CLang wrapper in other programming languages (i.e. Golang)
  typedef void* BackendWrapper;

  /*!
   * Creates the specific backend using the backend name
   * 
   * \param type backend name
   * \returns backend wrapper
   */
  BackendWrapper CreateBackend(char *type);

  /*!
   * Memory allocation cleanup
   * 
   * \param wrapper backend wrapper
   */
  void FreeBackend(BackendWrapper wrapper);

  /*!
   * Backend initialization method - initializes all the basic
   * parameters and behavior of a specific backend implementation
   * 
   * \param wrapper backend wrapper
   */
  void InitBackend(BackendWrapper wrapper);

  /*! 
   * Sets the specific homomorphic algorithm implementation
   * that backend provides
   * 
   * \param wrapper backend wrapper
   * \param algorithm homomorphic encryption algorithm
   */
  void SetBackendAlgorithm(BackendWrapper wrapper, char* algorithm);
  
  /*!
   * Returns the specific parameter
   * 
   * \param wrapper backend wrapper
   * \param key parameter name
   * \return parameter value
   */
  char* GetBackendParam(BackendWrapper wrapper, char* key);

  /*!
   * Sets the specific parameter
   * 
   * \param wrapper backend wrapper
   * \param key parameter name
   * \param value parameter value
   */
  void SetBackendParam(BackendWrapper wrapper, char* key, char* value);

  /*!
   * Generates the public/secret key pair
   * 
   * \param wrapper backend wrapper
   */
  void GenerateBackendKeys(BackendWrapper wrapper);

  /*!
   * Returns the UUEncoded public key
   * 
   * \param wrapper backend wrapper
   * \return public key
   */
  char* GetBackendPublicKey(BackendWrapper wrapper);

  /*!
   * Returns the UUEncoded secret key
   * 
   * \param wrapper backend wrapper
   * \return secret key
   */
  char* GetBackendSecretKey(BackendWrapper wrapper);

  /*!
   * Sets the public key 
   * 
   * \param wrapper backend wrapper
   * \param public_key UUEncoded public key
   */
  void SetBackendPublicKey(BackendWrapper wrapper, char* public_key);

  /*!
   * Sets the secret key 
   * 
   * \param wrapper backend wrapper
   * \param secret_key UUEncoded secret key
   */
  void SetBackendSecretKey(BackendWrapper wrapper, char* secret_key);

  /*!
   * Sets the both public and secret keys 
   * 
   * \param wrapper backend wrapper
   * \param public_key UUEncoded public key
   * \param secret_key UUEncoded secret key
   */
  void SetBackendKeys(BackendWrapper wrapper, char* public_key, char* secret_key);

  /*!
   * Returns the UUEncoded cipher containing ecrypted value, or vector of values
   * 
   * \param wrapper backend wrapper
   * \return UUEncoded cipher
   */
  char* GetBackendCipher(BackendWrapper wrapper);

  /*!
   * Sets the UUEncoded cipher containing ecrypted value, or vector of values
   * 
   * \param wrapper backend wrappers
   * \param cipher UUEncoded cipher
   */
  void SetBackendCipher(BackendWrapper wrapper, char* cipher);

  /*!
   * Encrypts the single value using the public key
   * 
   * \param wrapper backend wrapper
   * \param value value
   * \return UUEncoded cipher
   */
  char* BackendEncrypt(BackendWrapper wrapper, long value);

  /*!
   * Decrypts the single value using the secret key
   * 
   * \param wrapper backend wrapper
   * \return decrypted value
   */
  long BackendDecrypt(BackendWrapper wrapper);

  /*!
   * Adds the value to encrypted value
   * 
   * \param wrapper backend wrapper
   * \param value value
   */
  void BackendAdd(BackendWrapper wrapper, long value);

  /*!
   * Negates a single encrypted value, or a vector of encrypted values
   * 
   * \param wrapper backend wrapper
   */
  void BackendNegate(BackendWrapper wrapper);

  /*!
   * Multiplies the value with the encrypted value
   * 
   * \param wrapper backend wrapper
   * \param value value
   */
  void BackendMultiply(BackendWrapper wrapper, long value);

#ifdef __cplusplus
}
#endif