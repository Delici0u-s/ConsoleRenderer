#pragma once
#include <clocale>
#include <cstdint>
#include "Types/Point2D.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

inline void enableUtf8Console() {
#ifdef _WIN32
  // Set Windows console output code page to UTF-8.
  if (!SetConsoleOutputCP(CP_UTF8)) { throw "Console could not be activated as UTF-8, Aborting"; }

#else
  // On Linux and macOS, set the locale to the environment's default.
  if (setlocale(LC_ALL, "") == nullptr) { throw "Console could not be activated as UTF-8, Aborting"; }
#endif
}

enum class pos : uint8_t {
  topLeft = 1,
  midLeft = 1 << 1,
  botLeft = 1 << 2,
  topRight = 1 << 3,
  midRight = 1 << 4,
  botRight = 1 << 5,
};

namespace dCosnt {
constexpr float Grav{9.81};
constexpr Point2D GravV{0, (Grav * 0.1)};
} // namespace dCosnt