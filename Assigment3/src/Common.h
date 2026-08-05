#pragma once

#include <cassert>
#define TODO(msg) assert(false && (msg))
#define UNREACHABLE(msg) assert(false && "UNREACHABLE" && (msg));

#ifndef NDEBUG
#include <raylib.h>
  #define DEBUG(...) TraceLog(LOG_DEBUG,   __VA_ARGS__)
  #define INFO(...)  TraceLog(LOG_INFO,    __VA_ARGS__)
  #define WARN(...)  TraceLog(LOG_WARNING, __VA_ARGS__)
  #define ERROR(...) TraceLog(LOG_ERROR,   __VA_ARGS__)
#else 
  #define DEBUG(...)
  #define INFO(...)
  #define WARN(...)
  #define ERROR(...)
#endif //NDEBUG
