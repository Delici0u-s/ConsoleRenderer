#pragma once
#include <clocale>
#include <cstdint>
#include "Types/Point3D.hpp"

// If you want the application to print debug information uncomment the following line:
#define d_DEBUG

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
  topLeft = 1,        // 0x01
  UmidLeft = 1 << 1,  // 0x02
  DmidLeft = 1 << 2,  // 0x04
  botLeft = 1 << 6,   // 0x08
  topRight = 1 << 3,  // 0x10
  UmidRight = 1 << 4, // 0x20
  LmidRight = 1 << 5, // 0x40
  botRight = 1 << 7,  // 0x80
};

namespace dCosnt {
constexpr float Grav{9.81};
constexpr Point3D GravV{0, (Grav * 0.1)};
} // namespace dCosnt