
#pragma once
#include "Screen.hpp"
#include <vector>
#include <memory>
#include "../objects/DefaultObj.hpp"

class Renderer {
  Screen screen;
  std::vector<std::shared_ptr<DefaultObj>> &objpointer;

public:
  void DrawScreen();

  Renderer(unsigned int width, unsigned int height, std::vector<std::shared_ptr<DefaultObj>> &Objpointer) :
      screen(width, height), objpointer(Objpointer) {}

  constexpr unsigned int getWidth() const { return screen.m_width; }
  constexpr unsigned int getHeight() const { return screen.m_height; }
};
