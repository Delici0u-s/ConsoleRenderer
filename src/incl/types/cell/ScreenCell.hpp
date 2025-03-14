#pragma once
#include "charMap.hpp"
#include "../color/color256.hpp"
#include <sstream>

struct ScreenCell {
  Color256 color, bgColor;
  float bgColorZ, colorZ;
  charMap repres;

  constexpr void setColor(const Color256 &col, const float Z) {
    color = col;
    colorZ = Z;
  }

  constexpr void setbgColor(const Color256 &col, const float Z) {
    bgColor = col;
    bgColorZ = Z;
  }

  void reset() {
    repres.hideAll();
    color = {};
    bgColor = {};
  }
  void AddToPrintBuf(std::stringstream &s);
};