#include<string>
#include<utility>
#include<iostream>

#include "boolean_circuit_backend.hpp"
#include "boolean_circuit_backend_factory.hpp"
#include "clang_boolean_circuit_backend_interface.hpp"

using namespace std;
using namespace homomorphine;

BooleanCircuitBackendWrapper CreateBooleanCircuitBackend(char* type)
{
  string str_type(type);
  BooleanCircuitBackend* backend = BooleanCircuitBackendFactory::create(str_type);
  return (void*)backend;
}
  
void FreeBooleanCircuitBackend(BooleanCircuitBackendWrapper wrapper)
{
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper;
  delete backend;
}

void InitBooleanCircuitBackend(BooleanCircuitBackendWrapper wrapper)
{
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper;
  backend->init();
}

void SetBooleanCircuitBackendAlgorithm(BooleanCircuitBackendWrapper wrapper, char* algorithm)
{
  string str_algorithm(algorithm);
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper;

  backend->setAlgorithm(str_algorithm);
}

char* GetBooleanCircuitBackendParam(BooleanCircuitBackendWrapper wrapper, char* key) {
  string str_key(key);
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper;

  string value = backend->getParam(str_key);

  char* result = new char[value.length()+1];
  strcpy (result, value.c_str());

  return result;
}

void SetBooleanCircuitBackendParam(BooleanCircuitBackendWrapper wrapper, char* key, char* value)
{
  string str_key(key);
  string str_value(value);
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper;

  backend->setParam(str_key, str_value);
}

void GenerateBooleanCircuitBackendKeys(BooleanCircuitBackendWrapper wrapper)
{
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper;
  backend->generateKeys();
}

char* GetBooleanCircuitBackendPublicKey(BooleanCircuitBackendWrapper wrapper)
{
  stringstream stream;
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper;

  backend->writePublicKeyToStream(stream);
  string public_key = stream.str();

  char* result = new char[public_key.size()+1];
  strcpy (result, public_key.c_str());

  return result;
}

char* GetBooleanCircuitBackendSecretKey(BooleanCircuitBackendWrapper wrapper)
{
  stringstream stream;
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper;

  backend->writeSecretKeyToStream(stream);
  string secret_key = stream.str();

  char* result = new char[secret_key.length()+1];
  strcpy (result, secret_key.c_str());

  return result;
}

void SetBooleanCircuitBackendPublicKey(BooleanCircuitBackendWrapper wrapper, char* public_key)
{
  stringstream stream;
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper;

  stream << public_key;
  backend->readPublicKeyFromStream(stream);
}
  
void SetBooleanCircuitBackendSecretKey(BooleanCircuitBackendWrapper wrapper, char* secret_key)
{
  stringstream stream;
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper;

  stream << secret_key;
  backend->readSecretKeyFromStream(stream);
}

void SetBooleanCircuitBackendKeys(BooleanCircuitBackendWrapper wrapper, char* public_key, char* secret_key)
{
  stringstream public_key_stream;
  stringstream secret_key_stream;
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper;
  
  backend->readPublicKeyFromStream(public_key_stream);
  backend->readSecretKeyFromStream(secret_key_stream);
}

char* BooleanCircuitEncrypt(BooleanCircuitBackendWrapper wrapper, int value)
{
  stringstream stream;
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper;

  backend->encryptToStream(value, stream);
  string secret_key = stream.str();

  char* result = new char[secret_key.length()+1];
  strcpy (result, secret_key.c_str());

  return result;
}

char* BooleanCircuitEncode(BooleanCircuitBackendWrapper wrapper, int value)
{
  stringstream stream;
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper;

  backend->encodeToStream(value, stream);
  string secret_key = stream.str();

  char* result = new char[secret_key.length()+1];
  strcpy (result, secret_key.c_str());

  return result; 
}

int BooleanCircuitDecrypt(BooleanCircuitBackendWrapper wrapper, char* cipher)
{
  stringstream stream;
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper;

  stream << cipher;
  return backend->decryptFromStream(stream);
}

char* BooleanCircuitNOT(BooleanCircuitBackendWrapper wrapper, char* cipher)
{
  stringstream cipher_stream;
  stringstream result_stream;
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper;

  cipher_stream << cipher;

  backend->NOT(result_stream, cipher_stream);
  string result_str = result_stream.str();

  char* result = new char[result_str.length()+1];
  strcpy (result, result_str.c_str());

  return result;
}

char* BooleanCircuitCOPY(BooleanCircuitBackendWrapper wrapper, char* cipher)
{
  stringstream cipher_stream;
  stringstream result_stream;
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper;

  cipher_stream << cipher;

  backend->COPY(result_stream, cipher_stream);
  string result_str = result_stream.str();

  char* result = new char[result_str.length()+1];
  strcpy (result, result_str.c_str());

  return result;
}