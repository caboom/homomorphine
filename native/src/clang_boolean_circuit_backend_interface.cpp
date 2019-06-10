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

Blob GetBooleanCircuitBackendPublicKey(BooleanCircuitBackendWrapper wrapper)
{
  Blob result;
  long stream_size;
  stringstream stream;
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper;

  // fetch the public key
  backend->writePublicKeyToStream(stream);

  // return the content of stream
  return Util::copyStreamToBlob(stream);
}

Blob GetBooleanCircuitBackendSecretKey(BooleanCircuitBackendWrapper wrapper)
{
  Blob result;
  long stream_size;
  stringstream stream;
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper;

  // fetch the secret key
  backend->writeSecretKeyToStream(stream);
  
  // return the content of stream
  return Util::copyStreamToBlob(stream);
}

void SetBooleanCircuitBackendPublicKey(BooleanCircuitBackendWrapper wrapper, Blob public_key)
{
  stringstream stream;
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper;

  stream.write(public_key.content, public_key.size);
  backend->readPublicKeyFromStream(stream);
}
  
void SetBooleanCircuitBackendSecretKey(BooleanCircuitBackendWrapper wrapper, Blob secret_key)
{
  stringstream stream;
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper;

  stream.write(secret_key.content, secret_key.size);
  backend->readSecretKeyFromStream(stream);
}

void SetBooleanCircuitBackendKeys(BooleanCircuitBackendWrapper wrapper, Blob public_key, Blob secret_key)
{
  stringstream public_key_stream;
  stringstream secret_key_stream;
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper;
  
  backend->readPublicKeyFromStream(public_key_stream);
  backend->readSecretKeyFromStream(secret_key_stream);
}

Blob BooleanCircuitEncrypt(BooleanCircuitBackendWrapper wrapper, int value)
{
  Blob result;
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

Blob BooleanCircuitEncode(BooleanCircuitBackendWrapper wrapper, int value)
{
  Blob result;
  long stream_size;
  stringstream stream;
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper;

  // encode the stream
  backend->encodeToStream(value, stream);

  // return the content of stream
  return Util::copyStreamToBlob(stream);
}

int BooleanCircuitDecrypt(BooleanCircuitBackendWrapper wrapper, Blob cipher)
{
  stringstream stream;
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper;

  stream.write(cipher.content, cipher.size);
  return backend->decryptFromStream(stream);
}

Blob BooleanCircuitNOT(BooleanCircuitBackendWrapper wrapper, Blob cipher)
{
  stringstream cipher_stream;
  stringstream result_stream;
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper;

  // read the cipher to stream
  cipher_stream.write(cipher.content, cipher.size);

  // perform NOT operation
  backend->NOT(result_stream, cipher_stream);

  // copy result stream to blob
  return Util::copyStreamToBlob(result_stream);
}

Blob BooleanCircuitCOPY(BooleanCircuitBackendWrapper wrapper, Blob cipher)
{
  stringstream cipher_stream;
  stringstream result_stream;
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper;

  // read the cipher to stream
  cipher_stream.write(cipher.content, cipher.size);

  // perform COPY operation
  backend->COPY(result_stream, cipher_stream);

  // copy result stream to blob
  return Util::copyStreamToBlob(result_stream);
}

Blob BooleanCircuitNAND(BooleanCircuitBackendWrapper wrapper, Blob cipher_x, Blob cipher_y)
{
  stringstream cipher_x_stream;
  stringstream cipher_y_stream;
  stringstream result_stream;
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper; 

  // read the ciphers to stream
  cipher_x_stream.write(cipher_x.content, cipher_x.size);
  cipher_y_stream.write(cipher_y.content, cipher_y.size);

  // perform NAND operation
  backend->NAND(result_stream, cipher_x_stream, cipher_y_stream);

  // copy result stream to blob
  return Util::copyStreamToBlob(result_stream);
}

Blob BooleanCircuitOR(BooleanCircuitBackendWrapper wrapper, Blob cipher_x, Blob cipher_y)
{
  stringstream cipher_x_stream;
  stringstream cipher_y_stream;
  stringstream result_stream;
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper; 

  // read the ciphers to stream
  cipher_x_stream.write(cipher_x.content, cipher_x.size);
  cipher_y_stream.write(cipher_y.content, cipher_y.size);

  // perform OR operation
  backend->OR(result_stream, cipher_x_stream, cipher_y_stream);

  // copy result stream to Blob
  return Util::copyStreamToBlob(result_stream);
}

Blob BooleanCircuitAND(BooleanCircuitBackendWrapper wrapper, Blob cipher_x, Blob cipher_y)
{
  stringstream cipher_x_stream;
  stringstream cipher_y_stream;
  stringstream result_stream;
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper; 

  // read the ciphers to stream
  cipher_x_stream.write(cipher_x.content, cipher_x.size);
  cipher_y_stream.write(cipher_y.content, cipher_y.size);

  // perform AND operation
  backend->AND(result_stream, cipher_x_stream, cipher_y_stream);

  // copy result stream to blob
  return Util::copyStreamToBlob(result_stream);
}

Blob BooleanCircuitXOR(BooleanCircuitBackendWrapper wrapper, Blob cipher_x, Blob cipher_y)
{
  stringstream cipher_x_stream;
  stringstream cipher_y_stream;
  stringstream result_stream;
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper; 

  // read the ciphers to stream
  cipher_x_stream.write(cipher_x.content, cipher_x.size);
  cipher_y_stream.write(cipher_y.content, cipher_y.size);

  // perform XOR operation
  backend->XOR(result_stream, cipher_x_stream, cipher_y_stream);

  // copy result stream to blob 
  return Util::copyStreamToBlob(result_stream);
}

Blob BooleanCircuitXNOR(BooleanCircuitBackendWrapper wrapper, Blob cipher_x, Blob cipher_y)
{
  stringstream cipher_x_stream;
  stringstream cipher_y_stream;
  stringstream result_stream;
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper; 

  // read the ciphers to stream
  cipher_x_stream.write(cipher_x.content, cipher_x.size);
  cipher_y_stream.write(cipher_y.content, cipher_y.size);

  // perform XNOR operation
  backend->XNOR(result_stream, cipher_x_stream, cipher_y_stream);

  // copy result stream to Blob
  return Util::copyStreamToBlob(result_stream);
}

Blob BooleanCircuitNOR(BooleanCircuitBackendWrapper wrapper, Blob cipher_x, Blob cipher_y)
{
  stringstream cipher_x_stream;
  stringstream cipher_y_stream;
  stringstream result_stream;
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper; 

  // read the ciphers to stream
  cipher_x_stream.write(cipher_x.content, cipher_x.size);
  cipher_y_stream.write(cipher_y.content, cipher_y.size);

  // perform NOR operation
  backend->NOR(result_stream, cipher_x_stream, cipher_y_stream);

  // copy result stream to blob 
  return Util::copyStreamToBlob(result_stream);
}

Blob BooleanCircuitMUX(BooleanCircuitBackendWrapper wrapper, Blob cipher_x, Blob cipher_y, Blob cipher_z)
{
  stringstream cipher_x_stream;
  stringstream cipher_y_stream;
  stringstream cipher_z_stream;
  stringstream result_stream;
  BooleanCircuitBackend* backend = (BooleanCircuitBackend*)wrapper; 

  // read the ciphers to stream
  cipher_x_stream.write(cipher_x.content, cipher_x.size);
  cipher_y_stream.write(cipher_y.content, cipher_y.size);
  cipher_z_stream.write(cipher_z.content, cipher_z.size);

  // perform NOR operation
  backend->MUX(result_stream, cipher_x_stream, cipher_y_stream, cipher_z_stream);

  // copy result stream to blob
  return Util::copyStreamToBlob(result_stream);
}