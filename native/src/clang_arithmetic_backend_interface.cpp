#include<string>
#include<utility>
#include<iostream>

#include "arithmetic_backend.hpp"
#include "arithmetic_backend_factory.hpp"
#include "clang_arithmetic_backend_interface.hpp"

using namespace std;
using namespace homomorphine;

ArithmeticBackendWrapper CreateArithmeticBackend(char* type)
{
  string str_type(type);
  ArithmeticBackend* backend = ArithmeticBackendFactory::create(str_type);
  return (void*)backend;
}
  
void FreeArithmeticBackend(ArithmeticBackendWrapper wrapper)
{
  ArithmeticBackend* backend = (ArithmeticBackend*)wrapper;
  delete backend;
}

void InitArithmeticBackend(ArithmeticBackendWrapper wrapper)
{
  ArithmeticBackend* backend = (ArithmeticBackend*)wrapper;
  backend->init();
}

void SetArithmeticBackendAlgorithm(ArithmeticBackendWrapper wrapper, char* algorithm)
{
  string str_algorithm(algorithm);
  ArithmeticBackend* backend = (ArithmeticBackend*)wrapper;

  backend->setAlgorithm(str_algorithm);
}

char* GetArithmeticBackendParam(ArithmeticBackendWrapper wrapper, char* key) {
  string str_key(key);
  ArithmeticBackend* backend = (ArithmeticBackend*)wrapper;

  string value = backend->getParam(str_key);

  char* result = new char[value.length()+1];
  strcpy (result, value.c_str());

  return result;
}

void SetArithmeticBackendParam(ArithmeticBackendWrapper wrapper, char* key, char* value)
{
  string str_key(key);
  string str_value(value);
  ArithmeticBackend* backend = (ArithmeticBackend*)wrapper;

  backend->setParam(str_key, str_value);
}
  
void GenerateArithmeticBackendKeys(ArithmeticBackendWrapper wrapper)
{
  ArithmeticBackend* backend = (ArithmeticBackend*)wrapper;
  backend->generateKeys();
}

char* GetArithmeticBackendPublicKey(ArithmeticBackendWrapper wrapper)
{
  ArithmeticBackend* backend = (ArithmeticBackend*)wrapper;
  string public_key = backend->getPublicKey();

  char* result = new char[public_key.length()+1];
  strcpy (result, public_key.c_str());

  return result;
}

char* GetArithmeticBackendSecretKey(ArithmeticBackendWrapper wrapper)
{
  ArithmeticBackend* backend = (ArithmeticBackend*)wrapper;
  string secret_key = backend->getSecretKey();

  char* result = new char[secret_key.length()+1];
  strcpy (result, secret_key.c_str());

  return result;
}

void SetArithmeticBackendPublicKey(ArithmeticBackendWrapper wrapper, char* public_key)
{
  string str_public_key(public_key);
  ArithmeticBackend* backend = (ArithmeticBackend*)wrapper;

  backend->setPublicKey(str_public_key);
}
  
void SetArithmeticBackendSecretKey(ArithmeticBackendWrapper wrapper, char* secret_key)
{
  string str_secret_key(secret_key);
  ArithmeticBackend* backend = (ArithmeticBackend*)wrapper;
  
  backend->setSecretKey(str_secret_key);
}

void SetArithmeticBackendKeys(ArithmeticBackendWrapper wrapper, char* public_key, char* secret_key)
{
  string str_public_key(public_key);
  string str_secret_key(secret_key);
  ArithmeticBackend* backend = (ArithmeticBackend*)wrapper;
  
  backend->setPublicKey(str_public_key);
  backend->setSecretKey(str_secret_key);
}

char* GetArithmeticBackendCipher(ArithmeticBackendWrapper wrapper)
{
  ArithmeticBackend* backend = (ArithmeticBackend*)wrapper;
  string cipher = backend->getCipher();

  char* result = new char[cipher.length()+1];
  strcpy (result, cipher.c_str());

  return result;
}

void SetArithmeticBackendCipher(ArithmeticBackendWrapper wrapper, char* cipher)
{
  string str_cipher(cipher);
  ArithmeticBackend* backend = (ArithmeticBackend*)wrapper;
  
  backend->setCipher(str_cipher);
}

char* ArithmeticBackendEncrypt(ArithmeticBackendWrapper wrapper, long value)
{
  ArithmeticBackend* backend = (ArithmeticBackend*)wrapper;
  string cipher = backend->encrypt(value);

  char* result = new char[cipher.length()+1];
  strcpy (result, cipher.c_str());

  return result;
}

long ArithmeticBackendDecrypt(ArithmeticBackendWrapper wrapper)
{
  ArithmeticBackend* backend = (ArithmeticBackend*)wrapper;
  return backend->decrypt();
}

void ArithmeticBackendAdd(ArithmeticBackendWrapper wrapper, long value)
{
  ArithmeticBackend* backend = (ArithmeticBackend*)wrapper;
  backend->add(value);
}

void ArithmeticBackendNegate(ArithmeticBackendWrapper wrapper)
{
  ArithmeticBackend* backend = (ArithmeticBackend*)wrapper;
  backend->negate();
}

void ArithmeticBackendMultiply(ArithmeticBackendWrapper wrapper, long value)
{
  ArithmeticBackend* backend = (ArithmeticBackend*)wrapper;
  backend->multiply(value);
}