# Homomorphine

Homomorphine is a less stressful interface for various Homomorphic encryption libraries and algorithms. It's (ultimate) goal is to remove a complexity of using various homomorphic backends, try to do (semi)automated optimizations and noise management to reduce the implicit complexity of dealing with the homomorphic encryption. Currently supported backends are [SEAL](https://github.com/microsoft/SEAL) and [HELib](https://github.com/homenc/HElib) (*warning* HELib support is currently partially broken).

# Installation

You will have to install at least one of currently supported backend (either [SEAL](https://github.com/microsoft/SEAL) or [HELib](https://github.com/homenc/HElib)) and you will have to have C++14 compliant compiler, Basic Boost package(s) and CMake. On OS/X you can use Homebrew to install these:

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

# Warning 

Homomorphine-Go is currently not ready for production use and you should use SEAL with BFV algorithm for optimal results, atm.
