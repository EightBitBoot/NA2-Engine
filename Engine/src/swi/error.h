#pragma once

#define ERROR(x,...) printf("[ERROR] %s:%d | ", __FILE__, __LINE__); printf(x, __VA_ARGS__); __debugbreak()