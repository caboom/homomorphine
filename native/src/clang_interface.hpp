// foo.h
#ifdef __cplusplus
extern "C" {
#endif
  typedef void* SealWrapper;

  SealWrapper SealBackendCreate(void);
  void SealBackendFree(SealWrapper);
  void SealBackendInit(SealWrapper wrapper);
  void SealBackendSetAlgorithm(SealWrapper wrapper, char* algorithm);
  
  char* SealBackendGenerateEncodedPublicKey(SealWrapper wrapper);
  char* SealBackendGenerateEncodedSecretKey(SealWrapper wrapper);
  char** SealBackendGenerateEncodedKeys(SealWrapper wrapper);
  void SealBackendSetPublicKey(SealWrapper wrapper, char* public_key);
  void SealBackendSetSecretKey(SealWrapper wrapper, char* secret_key);
  void SealBackendSetKeys(SealWrapper wrapper, char* public_key, char* secret_key);
  char* SealBackendGetEncodedCipher(SealWrapper wrapper);
  void SealBackendSetEncodedCipher(SealWrapper wrapper, char* encoded_cipher);
  char* SealBackendEncryptValue(SealWrapper wrapper, int value);
  int SealBackendDecrypt(SealWrapper wrapper);
  void SealBackendAdd(SealWrapper wrapper, int value);
  void SealBackendNegate(SealWrapper wrapper);
  void SealBackendMultiply(SealWrapper wrapper, int value);
#ifdef __cplusplus
}
#endif