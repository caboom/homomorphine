// foo.h
#ifdef __cplusplus
extern "C" {
#endif
  typedef void* BackendWrapper;

  BackendWrapper BackendCreate(char *type);
  void BackendFree(BackendWrapper);
  void BackendInit(BackendWrapper wrapper);
  void BackendSetAlgorithm(BackendWrapper wrapper, char* algorithm);
  
  char* BackendGenerateEncodedPublicKey(BackendWrapper wrapper);
  char* BackendGenerateEncodedSecretKey(BackendWrapper wrapper);
  char** BackendGenerateEncodedKeys(BackendWrapper wrapper);
  void BackendSetPublicKey(BackendWrapper wrapper, char* public_key);
  void BackendSetSecretKey(BackendWrapper wrapper, char* secret_key);
  void BackendSetKeys(BackendWrapper wrapper, char* public_key, char* secret_key);
  char* BackendGetEncodedCipher(BackendWrapper wrapper);
  void BackendSetEncodedCipher(BackendWrapper wrapper, char* encoded_cipher);
  char* BackendEncryptValue(BackendWrapper wrapper, int value);
  int BackendDecrypt(BackendWrapper wrapper);
  void BackendAdd(BackendWrapper wrapper, int value);
  void BackendNegate(BackendWrapper wrapper);
  void BackendMultiply(BackendWrapper wrapper, int value);
#ifdef __cplusplus
}
#endif