#include "CellFragment.hpp"
#include <string>

std::string_view CellFragment::getChar() {
  static std::string buf;
  buf = "";
  // Unicode Braille base is U+2800.
  uint32_t codepoint = 0x2800 + repres.bits;

  if (codepoint <= 0x7F) {
    buf.push_back(static_cast<char>(codepoint));
  } else if (codepoint <= 0x7FF) {
    buf.push_back(static_cast<char>(0xC0 | ((codepoint >> 6) & 0x1F)));
    buf.push_back(static_cast<char>(0x80 | (codepoint & 0x3F)));
  } else if (codepoint <= 0xFFFF) {
    buf.push_back(static_cast<char>(0xE0 | ((codepoint >> 12) & 0x0F)));
    buf.push_back(static_cast<char>(0x80 | ((codepoint >> 6) & 0x3F)));
    buf.push_back(static_cast<char>(0x80 | (codepoint & 0x3F)));
  } else {
    buf.push_back(static_cast<char>(0xF0 | ((codepoint >> 18) & 0x07)));
    buf.push_back(static_cast<char>(0x80 | ((codepoint >> 12) & 0x3F)));
    buf.push_back(static_cast<char>(0x80 | ((codepoint >> 6) & 0x3F)));
    buf.push_back(static_cast<char>(0x80 | (codepoint & 0x3F)));
  }

  return buf;
}