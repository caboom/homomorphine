# Homomorphine

Homomorphine is a less stressful interface for various Homomorphic encryption libraries and algorithms. It's (ultimate) goal is to remove a complexity of using various homomorphic backends, try to do (semi)automated optimizations and noise management to reduce the implicit complexity of dealing with the homomorphic encryption. Currently supported backends are [SEAL](https://github.com/microsoft/SEAL) and [HELib](https://github.com/homenc/HElib) (*warning* HELib support is currently partially broken).

# Installation

You will have to install at least one of currently supported backend (either [SEAL](https://github.com/microsoft/SEAL) or [HELib](https://github.com/homenc/HElib)) and you will have to have C++14 compliant compiler (i.e. GCC 8/9), Basic Boost package(s) and CMake. On OS/X 10.14 and later you can use Homebrew to install these:

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

# Examples and usage

At the moment it's best to check the tests in the test folder for a basic usage, however, more examples are coming in near future.

# Homomorphine as a service

You can run Homomorphine as a service using homomorphine-service command:

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

# Warning 

Homomorphine-Go is currently not ready for production use and you should use SEAL with BFV algorithm for optimal results, atm.
