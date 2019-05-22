# Homomorphine

Homomorphine is a less stressful interface for various Homomorphic encryption libraries and algorithms. It's (ultimate) goal is to remove a complexity of using various homomorphic backends, try to do (semi)automated optimizations and noise management to reduce the implicit complexity of dealing with the homomorphic encryption. Currently supported backends are [SEAL](https://github.com/microsoft/SEAL) and [HELib](https://github.com/homenc/HElib) (*warning* HELib support is currently partially broken).

# Installation

You will have to install at least one of currently supported backend (either [SEAL](https://github.com/microsoft/SEAL) or [HELib](https://github.com/homenc/HElib)) and you will have to have C++14 compliant compiler, Basic Boost package(s) and CMake. On OS/X you can use Homebrew to install these:

```bash
$ brew install gcc boost cmake
```