# Homomorphine

Homomorphine is a less stressful interface for various Homomorphic encryption libraries and algorithms/models. Its (ultimate) goal is to remove a complexity of using various homomorphic backends, try to do (semi)automated optimizations and noise management to reduce the implicit complexity of dealing with the homomorphic encryption and implementation of various models providing a simple API, as well as CLang extensions that can be used to easily bind different programming languages to homomorphine and associated libraries. 

Currently supported aritmetic model backends are [SEAL](https://github.com/microsoft/SEAL) and [HELib](https://github.com/homenc/HElib) (**warning:** HELib support is currently partially broken). Homomorphine also supports boolean circuits models and it currently supports [TFHE](https://github.com/tfhe/tfhe) library. 

Homomorphine provides a different interface for arithmetic (modular and approximate number) and boolean circuit models given the different nature of operations performed on ciphers (boolean vs. numeric arithmetic operations).

# Installation

You will have to install at least one of currently supported backends (either [SEAL](https://github.com/microsoft/SEAL), [HELib](https://github.com/homenc/HElib), or [TFHE](https://github.com/tfhe/tfhe)) and you will have to have C++14 compatible compiler (i.e. GCC 8/9), basic Boost package(s) and CMake. On OS/X 10.14 and later you can use Homebrew to install these:

```shell
brew install gcc boost cmake
```

You can compile and install homomorphine using following commands:

```shell
cd native
cmake .
make -j9
make install
```

You can run the test suit using ctest:

```
ctest --verbose
```

Depending on your operating system and already installed libraries, you might also need libcrypto and openssl libraries (and relevant dev packages) in order to compile 

# Homomorphine as a service

For running homomorphine as a service you will need [cpprestsdk](https://github.com/microsoft/cpprestsdk), otherwise service executable won't be compiled. You can run Homomorphine as a service using homomorphine-service command:

```shell
./homomorphine-service --config=./config/devel.json
```

currently supported interface is only RESTFul HTTP interface (HTTPS is coming relatively soon) and configuration is relatively straightforward, i.e.:

```json
{
  "interfaces": {
    "http":{
      "host":"localhost",
      "port":"20888",
      "protocol":"http",
      "backend":"seal"
    }
  }
}
```

Homomorphine is not intended to be used as a service (this will be provided through the separate service that will be using [Homomorphine-Go](https://github.com/caboom/homomorphine-go) library), however, it can be practical at the times.

# Examples and documentation

At the moment it's best to check the tests in the test folder for a basic usage, however, more examples are coming in near future. Documentation can be found in the ./native/docs folder.

# Warning 

Homomorphine-Go is currently not ready for production use and you should use SEAL with BFV algorithm for optimal results, atm.
