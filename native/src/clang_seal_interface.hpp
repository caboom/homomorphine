#ifdef __cplusplus
extern "C" {
#endif
  #include "clang_types.hpp"

  typedef void* SealWrapper;

  SealWrapper SealBackendCreate(void);
  void SealBackendFree(SealWrapper wrapper);
  void SealBackendInit(SealWrapper wrapper);
  void SealBackendSetAlgorithm(SealWrapper wrapper, char* algorithm);
  
  char* SealBackendGeneratePublicKey(SealWrapper wrapper);
  char* SealBackendGenerateSecretKey(SealWrapper wrapper);
  char** SealBackendGenerateKeys(SealWrapper wrapper);
  char* SealBackendGetPublicKey(SealWrapper wrapper);
  char* SealBackendGetSecretKey(SealWrapper wrapper);
  char** SealBackendGetKeys(SealWrapper wrapper);
  void SealBackendSetPublicKey(SealWrapper wrapper, char* public_key);
  void SealBackendSetSecretKey(SealWrapper wrapper, char* secret_key);
  void SealBackendSetKeys(SealWrapper wrapper, char* public_key, char* secret_key);
  char* SealBackendGetCipher(SealWrapper wrapper);
  void SealBackendSetCipher(SealWrapper wrapper, char* ipher);
  char* SealBackendEncrypt(SealWrapper wrapper, uint_array_t values);
  uint_array_t SealBackendDecrypt(SealWrapper wrapper);
  void SealBackendAdd(SealWrapper wrapper, uint_array_t values);
  void SealBackendNegate(SealWrapper wrapper);
  void SealBackendMultiply(SealWrapper wrapper, uint_array_t values);
#ifdef __cplusplus
}
#endif