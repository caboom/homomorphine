#ifndef _HOMOMORPHINE_CLANG_TYPES_H_
#define _HOMOMORPHINE_CLANG_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif
  #include <stdint.h>
  #include <stddef.h>

  typedef struct uint_array_t {
    uint64_t* elements;
    size_t count;
  } uint_array_t;

#ifdef __cplusplus
}
#endif

#endif