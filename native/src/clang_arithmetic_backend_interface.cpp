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

bytes GetArithmeticBackendPublicKey(ArithmeticBackendWrapper wrapper)
{
  bytes result;
  long stream_size;
  stringstream stream;
  ArithmeticBackend* backend = (ArithmeticBackend*)wrapper;

  // fetch the public key
  backend->writePublicKeyToStream(stream);

  // return the content of stream
  return Util::copyStreamToBytes(stream);
}

bytes GetArithmeticBackendSecretKey(ArithmeticBackendWrapper wrapper)
{
  bytes result;
  long stream_size;
  stringstream stream;
  ArithmeticBackend* backend = (ArithmeticBackend*)wrapper;

  // fetch the public key
  backend->writeSecretKeyToStream(stream);

  // return the content of stream
  return Util::copyStreamToBytes(stream);
}

void SetArithmeticBackendPublicKey(ArithmeticBackendWrapper wrapper, bytes public_key)
{
  stringstream stream;
  ArithmeticBackend* backend = (ArithmeticBackend*)wrapper;

  stream.write(public_key.content, public_key.size);
  backend->readPublicKeyFromStream(stream);
}
  
void SetArithmeticBackendSecretKey(ArithmeticBackendWrapper wrapper, bytes secret_key)
{
  stringstream stream;
  ArithmeticBackend* backend = (ArithmeticBackend*)wrapper;

  stream.write(secret_key.content, secret_key.size);
  backend->readSecretKeyFromStream(stream);
}

void SetArithmeticBackendKeys(ArithmeticBackendWrapper wrapper, bytes public_key, bytes secret_key)
{
  stringstream public_key_stream;
  stringstream secret_key_stream;
  ArithmeticBackend* backend = (ArithmeticBackend*)wrapper;
  
  backend->readPublicKeyFromStream(public_key_stream);
  backend->readSecretKeyFromStream(secret_key_stream);
}

bytes GetArithmeticBackendCipher(ArithmeticBackendWrapper wrapper)
{
  bytes result;
  long stream_size;
  stringstream stream;
  ArithmeticBackend* backend = (ArithmeticBackend*)wrapper;

  // fetch the cipher stream
  backend->writeCipherToStream(stream);
  
  // return the content of stream
  return Util::copyStreamToBytes(stream);
}

void SetArithmeticBackendCipher(ArithmeticBackendWrapper wrapper, bytes cipher)
{
  stringstream stream;
  ArithmeticBackend* backend = (ArithmeticBackend*)wrapper;

  stream.write(cipher.content, cipher.size);
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