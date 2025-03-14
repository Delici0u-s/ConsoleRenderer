#pragma once
#include "charMap.hpp"
#include "../color/color256.hpp"
#include <limits>
#include <sstream>

struct ScreenCell {
  Color256 color, bgColor;
  float bgColorZ{std::numeric_limits<float>::lowest()}, colorZ{0};
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
    bgColorZ = std::numeric_limits<float>::lowest();
    colorZ = 0;
  }
  void AddToPrintBuf(std::stringstream &s);
};