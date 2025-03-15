#pragma once
#include "charMap.hpp"
#include "../color/color256.hpp"
#include <limits>
#include <sstream>

struct ScreenCell {
  Color256 color, bgColor;
  float bgColorZ{std::numeric_limits<float>::lowest()}, colorZ{0};
  charMap repres;

  void setColor(const Color256 &newColor, const float newZ);

  void setbgColor(const Color256 &newColor, const float newZ);

  void reset() {
    repres.hideAll();
    color = {};
    bgColor = {};
    bgColorZ = std::numeric_limits<float>::lowest();
    colorZ = 0;
  }
  void AddToPrintBuf(std::stringstream &s);
};