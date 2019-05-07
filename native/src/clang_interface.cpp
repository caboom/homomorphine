#include<string>
#include<utility>
#include<iostream>

#include "clang_interface.hpp"
#include "seal_backend.hpp"

using namespace std;
using namespace homomorphine;

SealWrapper SealBackendCreate(void)
{
  SealBackend* backend = new SealBackend();
  return (void*)backend;
}
  
void SealBackendFree(SealWrapper wrapper)
{
  SealBackend* backend = (SealBackend*)wrapper;
  delete backend;
}
  
void SealBackendInit(SealWrapper wrapper)
{
  SealBackend* backend = (SealBackend*)wrapper;
  backend->init();
}

void SealBackendSetAlgorithm(SealWrapper wrapper, char* algorithm)
{
  string str_algorithm(algorithm);
  SealBackend* backend = (SealBackend*)wrapper;

  backend->setAlgorithm(str_algorithm);
}

char* SealBackendGenerateEncodedPublicKey(SealWrapper wrapper)
{
  
  SealBackend* backend = (SealBackend*)wrapper;
  string public_key = backend->generateEncodedPublicKey();

  char* result = new char[public_key.length()+1];
  strcpy (result, public_key.c_str());

  return result;
}

char* SealBackendGenerateEncodedSecretKey(SealWrapper wrapper)
{
  SealBackend* backend = (SealBackend*)wrapper;
  string secret_key = backend->generateEncodedSecretKey();

  char* result = new char[secret_key.length()+1];
  strcpy (result, secret_key.c_str());

  return result;
}
  
char** SealBackendGenerateEncodedKeys(SealWrapper wrapper)
{
  char** result = new char*[2];
  SealBackend* backend = (SealBackend*)wrapper;

  pair<string, string> keys = backend->generateEncodedKeys();

  result[0] = new char[keys.first.length()+1];
  strcpy (result[0], keys.first.c_str());
  result[1] = new char[keys.second.length()+1];  
  strcpy (result[1], keys.second.c_str());

  return result;
}

void SealBackendSetPublicKey(SealWrapper wrapper, char* public_key)
{
  string str_public_key(public_key);
  SealBackend* backend = (SealBackend*)wrapper;

  backend->setPublicKey(str_public_key);
}
  
void SealBackendSetSecretKey(SealWrapper wrapper, char* secret_key)
{
  string str_secret_key(secret_key);
  SealBackend* backend = (SealBackend*)wrapper;
  
  backend->setSecretKey(str_secret_key);
}

void SealBackendSetKeys(SealWrapper wrapper, char* public_key, char* secret_key)
{
  string str_public_key(public_key);
  string str_secret_key(secret_key);
  SealBackend* backend = (SealBackend*)wrapper;
  
  backend->setPublicKey(str_public_key);
  backend->setSecretKey(str_secret_key);
}
  

char* SealBackendGetEncodedCipher(SealWrapper wrapper)
{
  SealBackend* backend = (SealBackend*)wrapper;
  string cipher = backend->getEncodedCipher();

  char* result = new char[cipher.length()+1];
  strcpy (result, cipher.c_str());

  return result;
}

void SealBackendSetEncodedCipher(SealWrapper wrapper, char* encoded_cipher)
{
  string str_encoded_cipher(encoded_cipher);
  SealBackend* backend = (SealBackend*)wrapper;
  
  backend->setEncodedCipher(str_encoded_cipher);
}
  
char* SealBackendEncryptValue(SealWrapper wrapper, int value)
{
  SealBackend* backend = (SealBackend*)wrapper;
  string cipher = backend->encryptValue(value);

  char* result = new char[cipher.length()+1];
  strcpy (result, cipher.c_str());

  return result;
}

int SealBackendDecrypt(SealWrapper wrapper)
{
  SealBackend* backend = (SealBackend*)wrapper;
  return backend->decrypt();
}

void SealBackendAdd(SealWrapper wrapper, int value)
{
  SealBackend* backend = (SealBackend*)wrapper;
  backend->add(value);
}

void SealBackendNegate(SealWrapper wrapper)
{
  SealBackend* backend = (SealBackend*)wrapper;
  backend->negate();
}
  
void SealBackendMultiply(SealWrapper wrapper, int value)
{
  SealBackend* backend = (SealBackend*)wrapper;
  backend->multiply(value);
}