#pragma once
#include "Screen.hpp"
#include "../objects/basicObj.hpp"
#include <vector>

class Renderer {
  Screen screen;
  std::vector<basicObj> &objpointer;

public:
  void DrawScreen();

  Renderer(unsigned int width, unsigned int height, std::vector<basicObj> &Objpointer) :
      screen(width, height), objpointer(Objpointer) {}

  constexpr unsigned int getWidth() const { return screen.m_width; }
  constexpr unsigned int getHeight() const { return screen.m_height; }
};