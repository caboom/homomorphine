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
} long_array_t;

#ifdef __cplusplus
}
#endif

#endif