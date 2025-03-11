#include "Renderer.hpp"
#include "Screen.hpp"
#include <cstdio>
#include <iostream>

void Renderer::DrawScreen() {
  // std::cout << "EnteringDrawScreen\n";
  screen.clear();
  // std::cout << "HowDraws:\n";
  for (auto &i : objpointer)
    i.howDraw(screen);
  // std::cout << "WriteBuf:\n";
  screen.WriteBuffer();
  // std::cout << "Printing\n";
  std::cout << screen.printbuf.rdbuf();

  // std::cout << "donePrinting\n";
}