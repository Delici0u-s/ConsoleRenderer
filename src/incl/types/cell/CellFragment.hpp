#pragma once
#include "charMap.hpp"
#include "../color/color256.hpp"
#include <string_view>

struct CellFragment {
  Color256 color{0, 0, 0}, bgColor{0, 0, 0};
  charMap repres;
  std::string_view getChar();
};