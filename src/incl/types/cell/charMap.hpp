#pragma once
#include <cstdint>
#include "../../general.hpp"
#include <string_view>
#include <string>

struct charMap {
  float zpos{0}, Czops{-1};
  std::string Tchar{' '};

  const std::string_view getChar() const;
  constexpr void setChar(const std::string_view cha, const float z) {
    Tchar = cha;
    Czops = z;
  }

  uint8_t bits{};
  void show(pos);
  void show(uint8_t);
  void showAll();
  void hide(pos);
  void hide(uint8_t);
  void hideAll();
};