#ifndef INCLUDE_VIDA_TYPES_H_
#define INCLUDE_VIDA_TYPES_H_

typedef char int8;
typedef short int16;
typedef int int32;
typedef long int64;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned uint32;
typedef unsigned long uint64;

typedef struct {
  float x, y;
} vec2_t;

typedef struct {
  float x, y, z;
} vec3_t;

#endif // !INCLUDE_VIDA_TYPES_H_
