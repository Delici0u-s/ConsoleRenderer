#pragma once
#include <cstdint>
#include "../../general.hpp"
struct charMap {
  uint8_t bits{};

  void show(pos);
  void show(uint8_t);
  void showAll();
  void hide(pos);
  void hide(uint8_t);
  void hideAll();
};
