#include "charMap.hpp"
#include <cstdint>
#include <string_view>
#include <string>

void charMap::show(pos p) { bits |= static_cast<uint8_t>(p); }
void charMap::show(uint8_t p) { bits |= p; }
void charMap::showAll() { bits = 0xFF; }
void charMap::hide(pos p) { bits &= (0xFF ^ static_cast<uint8_t>(p)); }
void charMap::hide(uint8_t p) { bits &= (0xFF ^ p); }
void charMap::hideAll() { bits = 0; }

const std::string_view charMap::getChar() const {
  if (Czops >= zpos) return Tchar;
  static std::string buf;
  buf = "";
  // Unicode Braille base is U+2800.
  uint32_t codepoint = 0x2800 + bits;

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

// std::string_view charMap::getChar() const {
//   // If Czops >= zpos, use the stored character (Tchar)
//   if (Czops >= zpos) return Tchar;

//   // Otherwise, compute the Braille character from 'bits'
//   uint32_t ch = 0x2800 + bits;
//   static std::string out;

//   // Since Braille codepoints (U+2800–U+28FF) are always above 0x7FF,
//   // the third branch (for ch <= 0xFFFF) is what’s normally used.
//   if (ch <= 0x7F) {
//     out.push_back(static_cast<char>(ch));
//   } else if (ch <= 0x7FF) {
//     out.push_back(static_cast<char>(0xC0 | ((ch >> 6) & 0x1F)));
//     out.push_back(static_cast<char>(0x80 | (ch & 0x3F)));
//   } else if (ch <= 0xFFFF) {
//     out.push_back(static_cast<char>(0xE0 | ((ch >> 12) & 0x0F)));
//     out.push_back(static_cast<char>(0x80 | ((ch >> 6) & 0x3F)));
//     out.push_back(static_cast<char>(0x80 | (ch & 0x3F)));
//   } else {
//     out.push_back(static_cast<char>(0xF0 | ((ch >> 18) & 0x07)));
//     out.push_back(static_cast<char>(0x80 | ((ch >> 12) & 0x3F)));
//     out.push_back(static_cast<char>(0x80 | ((ch >> 6) & 0x3F)));
//     out.push_back(static_cast<char>(0x80 | (ch & 0x3F)));
//   }
//   return out;
// }