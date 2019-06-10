#ifndef _HOMOMORPHINE_CLANG_TYPES_H_
#define _HOMOMORPHINE_CLANG_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

//! Wrapper around the array, or vector of values
typedef struct long_array_t {
  long* elements;
  size_t count;
} LongArray;

//! Wrapper around the char/byte array
typedef struct blob_t {
  char* content;
  long size;
} Blob;

#ifdef __cplusplus
}
#endif

#endif