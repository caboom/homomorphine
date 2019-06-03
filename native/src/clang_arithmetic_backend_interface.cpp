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
  stringstream stream;
  ArithmeticBackend* backend = (ArithmeticBackend*)wrapper;

  backend->writePublicKeyToStream(stream);
  string public_key = stream.str();

  char* result = new char[public_key.size()+1];
  strcpy (result, public_key.c_str());

  return result;
}

char* GetArithmeticBackendSecretKey(ArithmeticBackendWrapper wrapper)
{
  stringstream stream;
  ArithmeticBackend* backend = (ArithmeticBackend*)wrapper;

  backend->writeSecretKeyToStream(stream);
  string secret_key = stream.str();

  char* result = new char[secret_key.length()+1];
  strcpy (result, secret_key.c_str());

  return result;
}

void SetArithmeticBackendPublicKey(ArithmeticBackendWrapper wrapper, char* public_key)
{
  stringstream stream;
  ArithmeticBackend* backend = (ArithmeticBackend*)wrapper;

  stream << public_key;
  backend->readPublicKeyFromStream(stream);
}
  
void SetArithmeticBackendSecretKey(ArithmeticBackendWrapper wrapper, char* secret_key)
{
  stringstream stream;
  ArithmeticBackend* backend = (ArithmeticBackend*)wrapper;

  stream << secret_key;
  backend->readSecretKeyFromStream(stream);
}

void SetArithmeticBackendKeys(ArithmeticBackendWrapper wrapper, char* public_key, char* secret_key)
{
  stringstream public_key_stream;
  stringstream secret_key_stream;
  ArithmeticBackend* backend = (ArithmeticBackend*)wrapper;
  
  backend->readPublicKeyFromStream(public_key_stream);
  backend->readSecretKeyFromStream(secret_key_stream);
}

char* GetArithmeticBackendCipher(ArithmeticBackendWrapper wrapper)
{
  stringstream stream;
  ArithmeticBackend* backend = (ArithmeticBackend*)wrapper;

  backend->writeCipherToStream(stream);
  string cipher = stream.str();

  char* result = new char[cipher.length()+1];
  strcpy (result, cipher.c_str());

  return result;
}

void SetArithmeticBackendCipher(ArithmeticBackendWrapper wrapper, char* cipher)
{
  stringstream stream;
  ArithmeticBackend* backend = (ArithmeticBackend*)wrapper;

  stream << cipher;
  
  backend->readCipherFromStream(stream);
}

void ArithmeticBackendEncrypt(ArithmeticBackendWrapper wrapper, long value)
{
  ArithmeticBackend* backend = (ArithmeticBackend*)wrapper;

  backend->encrypt(value);
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