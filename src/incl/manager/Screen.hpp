#pragma once
#include "../types/cell/ScreenCell.hpp"
#include <sstream>
#include <vector>

class Renderer;
class Screen {
public:
  const unsigned int m_width;
  const unsigned int m_height;
  std::vector<ScreenCell> framebuffer{};

  Screen(unsigned int width, unsigned int height) : m_width{width}, m_height{height}, framebuffer(width * height) {}

  friend Renderer;
  ScreenCell &get(unsigned int X, unsigned int Y);

protected:
  void clear();
  void WriteBuffer();
  std::stringstream printbuf{};
};