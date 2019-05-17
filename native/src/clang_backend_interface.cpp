#include<string>
#include<utility>
#include<iostream>

#include "backend.hpp"
#include "backend_factory.hpp"
#include "clang_backend_interface.hpp"

using namespace std;
using namespace homomorphine;

BackendWrapper CreateBackend(char* type)
{
  string str_type(type);
  Backend* backend = BackendFactory::create(str_type);
  return (void*)backend;
}
  
void FreeBackend(BackendWrapper wrapper)
{
  Backend* backend = (Backend*)wrapper;
  delete backend;
}

void InitBackend(BackendWrapper wrapper)
{
  Backend* backend = (Backend*)wrapper;
  backend->init();
}

void SetBackendAlgorithm(BackendWrapper wrapper, char* algorithm)
{
  string str_algorithm(algorithm);
  Backend* backend = (Backend*)wrapper;

  backend->setAlgorithm(str_algorithm);
}

char* GenerateBackendPublicKey(BackendWrapper wrapper)
{
  Backend* backend = (Backend*)wrapper;
  string public_key = backend->generatePublicKey();

  char* result = new char[public_key.length()+1];
  strcpy (result, public_key.c_str());

  return result;
}

char* GenerateBackendSecretKey(BackendWrapper wrapper)
{
  Backend* backend = (Backend*)wrapper;
  string secret_key = backend->generateSecretKey();

  char* result = new char[secret_key.length()+1];
  strcpy (result, secret_key.c_str());

  return result;
}
  
char** GenerateBackendKeys(BackendWrapper wrapper)
{
  char** result = new char*[2];
  Backend* backend = (Backend*)wrapper;

  pair<string, string> keys = backend->generateKeys();

  result[0] = new char[keys.first.length()+1];
  strcpy (result[0], keys.first.c_str());
  result[1] = new char[keys.second.length()+1];  
  strcpy (result[1], keys.second.c_str());

  return result;
}

char* GetBackendPublicKey(BackendWrapper wrapper)
{
  Backend* backend = (Backend*)wrapper;
  string public_key = backend->getPublicKey();

  char* result = new char[public_key.length()+1];
  strcpy (result, public_key.c_str());

  return result;
}

char* GetBackendSecretKey(BackendWrapper wrapper)
{
  Backend* backend = (Backend*)wrapper;
  string secret_key = backend->getSecretKey();

  char* result = new char[secret_key.length()+1];
  strcpy (result, secret_key.c_str());

  return result;
}

char** GetBackendKeys(BackendWrapper wrapper)
{
  char** result = new char*[2];
  Backend* backend = (Backend*)wrapper;

  pair<string, string> keys = backend->getKeys();

  result[0] = new char[keys.first.length()+1];
  strcpy (result[0], keys.first.c_str());
  result[1] = new char[keys.second.length()+1];  
  strcpy (result[1], keys.second.c_str());

  return result;
}

void SetBackendPublicKey(BackendWrapper wrapper, char* public_key)
{
  string str_public_key(public_key);
  Backend* backend = (Backend*)wrapper;

  backend->setPublicKey(str_public_key);
}
  
void SetBackendSecretKey(BackendWrapper wrapper, char* secret_key)
{
  string str_secret_key(secret_key);
  Backend* backend = (Backend*)wrapper;
  
  backend->setSecretKey(str_secret_key);
}

void SetBackendKeys(BackendWrapper wrapper, char* public_key, char* secret_key)
{
  string str_public_key(public_key);
  string str_secret_key(secret_key);
  Backend* backend = (Backend*)wrapper;
  
  backend->setPublicKey(str_public_key);
  backend->setSecretKey(str_secret_key);
}

char* GetBackendCipher(BackendWrapper wrapper)
{
  Backend* backend = (Backend*)wrapper;
  string cipher = backend->getCipher();

  char* result = new char[cipher.length()+1];
  strcpy (result, cipher.c_str());

  return result;
}

void SetBackendCipher(BackendWrapper wrapper, char* cipher)
{
  string str_cipher(cipher);
  Backend* backend = (Backend*)wrapper;
  
  backend->setCipher(str_cipher);
}

char* BackendEncrypt(BackendWrapper wrapper, uint_array_t values)
{
  std::vector<uint64_t> ser_values;
  SealBackend* backend = (SealBackend*)wrapper;

  for(int i = 0; i < values.count; i++) {
    ser_values.push_back(values.elements[i]);
  }

  string cipher = backend->encrypt(ser_values);

  char* result = new char[cipher.length()+1];
  strcpy (result, cipher.c_str());

  return result;
}

uint_array_t BackendDecrypt(BackendWrapper wrapper)
{
  uint_array_t result;
  SealBackend* backend = (SealBackend*)wrapper;
  vector<uint64_t> decrypted_list = backend->decryptValues();

  result.count = decrypted_list.size();
  result.elements = (uint64_t *)calloc(decrypted_list.size(), sizeof(uint64_t));

  int i = 0;
  for (const int& element : decrypted_list) {
    memcpy(&result.elements[i], &element, sizeof(uint64_t));
    i++;
  }

  return result;
}

void BackendAdd(BackendWrapper wrapper, uint_array_t values)
{
  vector<uint64_t> values_vector;
  Backend* backend = (Backend*)wrapper;
  for (int i = 0; i < values.count; i++) {
    values_vector.push_back(values.elements[i]);
  }

  backend->add(values_vector);
}

void BackendNegate(BackendWrapper wrapper)
{
  Backend* backend = (Backend*)wrapper;
  backend->negate();
}
  
void BackendMultiply(BackendWrapper wrapper, uint_array_t values)
{
  vector<uint64_t> values_vector;
  Backend* backend = (Backend*)wrapper;
  for (int i = 0; i < values.count; i++) {
    values_vector.push_back(values.elements[i]);
  }

  backend->multiply(values_vector);
}