#pragma once

#define V2D_CHECK(BOOL)                                                        \
  if (!(BOOL)) {                                                               \
    return false;                                                              \
  }
