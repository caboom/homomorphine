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

bytes GetBooleanCircuitBackendPublicKey(BooleanCircuitBackendWrapper wrapper)
{
  bytes result;
  long stream_size;
  stringstream stream;
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper;

  // fetch the public key
  backend->writePublicKeyToStream(stream);

  // read the content
  stream_size = Util::getStreamSize(stream);
  char* content = new char[stream_size+1];
  stream.read(content, stream_size);

  // package and return POD result
  result.content = content;
  result.size = stream_size;

  return result;
}

bytes GetBooleanCircuitBackendSecretKey(BooleanCircuitBackendWrapper wrapper)
{
  bytes result;
  long stream_size;
  stringstream stream;
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper;

  // fetch the secret key
  backend->writeSecretKeyToStream(stream);
  
  // read the content
  stream_size = Util::getStreamSize(stream);
  char* content = new char[stream_size+1];
  stream.read(content, stream_size);

  // package and return POD result
  result.content = content;
  result.size = stream_size;

  return result;
}

void SetBooleanCircuitBackendPublicKey(BooleanCircuitBackendWrapper wrapper, bytes public_key)
{
  stringstream stream;
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper;

  stream.write(public_key.content, public_key.size);
  backend->readPublicKeyFromStream(stream);
}
  
void SetBooleanCircuitBackendSecretKey(BooleanCircuitBackendWrapper wrapper, bytes secret_key)
{
  stringstream stream;
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper;

  stream.write(secret_key.content, secret_key.size);
  backend->readSecretKeyFromStream(stream);
}

void SetBooleanCircuitBackendKeys(BooleanCircuitBackendWrapper wrapper, bytes public_key, bytes secret_key)
{
  stringstream public_key_stream;
  stringstream secret_key_stream;
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper;
  
  backend->readPublicKeyFromStream(public_key_stream);
  backend->readSecretKeyFromStream(secret_key_stream);
}

bytes BooleanCircuitEncrypt(BooleanCircuitBackendWrapper wrapper, int value)
{
  bytes result;
  long stream_size;
  stringstream stream;
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper;

  // encrypt to stream
  backend->encryptToStream(value, stream);

  // read the content
  stream_size = Util::getStreamSize(stream);
  char* content = new char[stream_size+1];
  stream.read(content, stream_size);

  // package and return POD result
  result.content = content;
  result.size = stream_size;

  return result;
}

bytes BooleanCircuitEncode(BooleanCircuitBackendWrapper wrapper, int value)
{
  bytes result;
  long stream_size;
  stringstream stream;
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper;

  // encode the stream
  backend->encodeToStream(value, stream);

  // read the content
  stream_size = Util::getStreamSize(stream);
  char* content = new char[stream_size+1];
  stream.read(content, stream_size);

  // package and return POD result
  result.content = content;
  result.size = stream_size;

  return result;
}

int BooleanCircuitDecrypt(BooleanCircuitBackendWrapper wrapper, bytes cipher)
{
  stringstream stream;
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper;

  stream.write(cipher.content, cipher.size);
  return backend->decryptFromStream(stream);
}

bytes BooleanCircuitNOT(BooleanCircuitBackendWrapper wrapper, bytes cipher)
{
  bytes result;
  long stream_size;
  stringstream cipher_stream;
  stringstream result_stream;
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper;

  // read the cipher to stream
  cipher_stream.write(cipher.content, cipher.size);

  // perform NOT operation
  backend->NOT(result_stream, cipher_stream);

  // read the content
  stream_size = Util::getStreamSize(result_stream);
  char* content = new char[stream_size+1];
  result_stream.read(content, stream_size);

  // package and return POD result
  result.content = content;
  result.size = stream_size;

  return result;
}

bytes BooleanCircuitCOPY(BooleanCircuitBackendWrapper wrapper, bytes cipher)
{
  bytes result;
  long stream_size;
  stringstream cipher_stream;
  stringstream result_stream;
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper;

  // read the cipher to stream
  cipher_stream.write(cipher.content, cipher.size);

  // perform COPY operation
  backend->COPY(result_stream, cipher_stream);

  // read the content
  stream_size = Util::getStreamSize(result_stream);
  char* content = new char[stream_size+1];
  result_stream.read(content, stream_size);

  // package and return POD result
  result.content = content;
  result.size = stream_size;

  return result;
}