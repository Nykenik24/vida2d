#ifndef INCLUDE_VIDA_LOGGER_H_
#define INCLUDE_VIDA_LOGGER_H_

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
  VIDA_LOG_DEBUG,
  VIDA_LOG_INFO,
  VIDA_LOG_WARN,
  VIDA_LOG_ERR,
  VIDA_LOG_FATAL,
} log_level_t;

extern log_level_t vida_min_log_level;

inline const char *level_to_str(log_level_t level) {
  switch (level) {
  case VIDA_LOG_DEBUG:
    return "DEBUG";
  case VIDA_LOG_INFO:
    return "INFO";
  case VIDA_LOG_WARN:
    return "WARN";
  case VIDA_LOG_ERR:
    return "ERR";
  case VIDA_LOG_FATAL:
    return "FATAL";
  }
  return "UNKNOWN";
}

inline void vida_log(log_level_t level, const char *fmt, ...) {
  if (level >= vida_min_log_level) {
    va_list args;
    va_start(args, fmt);
    printf("[%s] ", level_to_str(level));
    vprintf(fmt, args);
    printf("\n");
    va_end(args);
  }

  if (level == VIDA_LOG_FATAL) {
    exit(1);
  }
}
inline void vida_set_minlog(log_level_t min) { vida_min_log_level = min; }

#endif // !INCLUDE_VIDA_LOGGER_H_
