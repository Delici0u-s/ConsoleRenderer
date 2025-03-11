#include "charMap.hpp"
#include <cstdint>

void charMap::show(pos p) { bits |= static_cast<uint8_t>(p); }
void charMap::show(uint8_t p) { bits |= p; }
void charMap::showAll() { bits = 0x3F; }
void charMap::hide(pos p) { bits &= (0xFF ^ static_cast<uint8_t>(p)); }
void charMap::hide(uint8_t p) { bits &= (0xFF ^ p); }
void charMap::hideAll() { bits = 0; }