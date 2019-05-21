#ifdef __cplusplus
extern "C" {
#endif
  #include "clang_types.hpp"

  typedef void* BackendWrapper;

  BackendWrapper CreateBackend(char *type);
  void FreeBackend(BackendWrapper wrapper);
  void InitBackend(BackendWrapper wrapper);
  void SetBackendAlgorithm(BackendWrapper wrapper, char* algorithm);
  
  char* GetBackendParam(BackendWrapper wrapper, char* key);
  void SetBackendParam(BackendWrapper wrapper, char* key, char* value);
  void GenerateBackendKeys(BackendWrapper wrapper);
  char* GetBackendPublicKey(BackendWrapper wrapper);
  char* GetBackendSecretKey(BackendWrapper wrapper);
  void SetBackendPublicKey(BackendWrapper wrapper, char* public_key);
  void SetBackendSecretKey(BackendWrapper wrapper, char* secret_key);
  void SetBackendKeys(BackendWrapper wrapper, char* public_key, char* secret_key);
  char* GetBackendCipher(BackendWrapper wrapper);
  void SetBackendCipher(BackendWrapper wrapper, char* cipher);
  char* BackendEncrypt(BackendWrapper wrapper, long value);
  long BackendDecrypt(BackendWrapper wrapper);
  void BackendAdd(BackendWrapper wrapper, long value);
  void BackendNegate(BackendWrapper wrapper);
  void BackendMultiply(BackendWrapper wrapper, long value);

#ifdef __cplusplus
}
#endif