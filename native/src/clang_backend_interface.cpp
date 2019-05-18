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
  
void GenerateBackendKeys(BackendWrapper wrapper)
{
  Backend* backend = (Backend*)wrapper;
  backend->generateKeys();
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

char* BackendEncrypt(BackendWrapper wrapper, int value)
{
  Backend* backend = (Backend*)wrapper;
  string cipher = backend->encrypt(value);

  char* result = new char[cipher.length()+1];
  strcpy (result, cipher.c_str());

  return result;
}

int BackendDecrypt(BackendWrapper wrapper)
{
  Backend* backend = (Backend*)wrapper;
  return backend->decrypt();
}

void BackendAdd(BackendWrapper wrapper, int value)
{
  Backend* backend = (Backend*)wrapper;
  backend->add(value);
}

void BackendNegate(BackendWrapper wrapper)
{
  Backend* backend = (Backend*)wrapper;
  backend->negate();
}

void BackendMultiply(BackendWrapper wrapper, int value)
{
  Backend* backend = (Backend*)wrapper;
  backend->multiply(value);
}