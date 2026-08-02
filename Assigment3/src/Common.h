#pragma once

#include <cassert>
#define TODO(msg) assert(false && (msg))
#define UNREACHABLE(msg) assert(false && "UNREACHABLE" && (msg));
