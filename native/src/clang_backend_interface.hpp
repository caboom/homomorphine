#ifdef __cplusplus
extern "C" {
#endif
  #include "clang_types.hpp"

  typedef void* BackendWrapper;

  BackendWrapper BackendCreate(char *type);
  void BackendFree(BackendWrapper wrapper);
  void BackendInit(BackendWrapper wrapper);
  void BackendSetAlgorithm(BackendWrapper wrapper, char* algorithm);
  
  char* BackendGeneratePublicKey(BackendWrapper wrapper);
  char* BackendGenerateSecretKey(BackendWrapper wrapper);
  char** BackendGenerateKeys(BackendWrapper wrapper);
  char* BackendGetPublicKey(BackendWrapper wrapper);
  char* BackendGetSecretKey(BackendWrapper wrapper);
  char** BackendGetKeys(BackendWrapper wrapper);
  void BackendSetPublicKey(BackendWrapper wrapper, char* public_key);
  void BackendSetSecretKey(BackendWrapper wrapper, char* secret_key);
  void BackendSetKeys(BackendWrapper wrapper, char* public_key, char* secret_key);
  char* BackendGetCipher(BackendWrapper wrapper);
  void BackendSetCipher(BackendWrapper wrapper, char* cipher);
  char* BackendEncrypt(BackendWrapper wrapper, uint_array_t values);
  uint_array_t BackendDecrypt(BackendWrapper wrapper);
  void BackendAdd(BackendWrapper wrapper, uint_array_t values);
  void BackendNegate(BackendWrapper wrapper);
  void BackendMultiply(BackendWrapper wrapper, uint_array_t values);
#ifdef __cplusplus
}
#endif