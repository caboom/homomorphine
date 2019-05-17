#ifdef __cplusplus
extern "C" {
#endif
  #include "clang_types.hpp"

  typedef void* BackendWrapper;

  BackendWrapper CreateBackend(char *type);
  void FreeBackend(BackendWrapper wrapper);
  void InitBackend(BackendWrapper wrapper);
  void SetBackendAlgorithm(BackendWrapper wrapper, char* algorithm);
  
  char* GenerateBackendPublicKey(BackendWrapper wrapper);
  char* GenerateBackendSecretKey(BackendWrapper wrapper);
  char** GenerateBackendKeys(BackendWrapper wrapper);
  char* GetBackendPublicKey(BackendWrapper wrapper);
  char* GetBackendSecretKey(BackendWrapper wrapper);
  char** GetBackendKeys(BackendWrapper wrapper);
  void SetBackendPublicKey(BackendWrapper wrapper, char* public_key);
  void SetBackendSecretKey(BackendWrapper wrapper, char* secret_key);
  void SetBackendKeys(BackendWrapper wrapper, char* public_key, char* secret_key);
  char* GetBackendCipher(BackendWrapper wrapper);
  void SetBackendCipher(BackendWrapper wrapper, char* cipher);
  char* BackendEncrypt(BackendWrapper wrapper, uint_array_t values);
  uint_array_t BackendDecrypt(BackendWrapper wrapper);
  void BackendAdd(BackendWrapper wrapper, uint_array_t values);
  void BackendNegate(BackendWrapper wrapper);
  void BackendMultiply(BackendWrapper wrapper, uint_array_t values);
#ifdef __cplusplus
}
#endif