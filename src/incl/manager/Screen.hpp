#pragma once
#include "../types/cell/ScreenCell.hpp"
#include <sstream>
#include <vector>

class Screen {
public:
  const unsigned int m_width;
  const unsigned int m_height;
  std::vector<ScreenCell> framebuffer{};
  std::stringstream printbuf{};

  Screen(unsigned int width, unsigned int height) : m_width{width}, m_height{height}, framebuffer(width * height) {}

  void clear();
  void WriteBuffer();
};