#pragma once
#include "charMap.hpp"
#include "../color/color256.hpp"
#include <string_view>

struct ScreenCell {
  Color256 color, bgColor;
  charMap repres;
  std::string_view getChar();

  void reset() {
    repres.hideAll();
    color = {};
    bgColor = {};
  }
};