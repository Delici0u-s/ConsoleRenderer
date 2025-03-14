// #include "Renderer.hpp"
// #include "Screen.hpp"
// #include <iostream>

// void Renderer::DrawScreen() {
//   screen.clear();
//   for (auto &obj : objpointer)
//     obj.howDraw(screen);
//   screen.WriteBuffer();
//   std::cout << screen.printbuf.rdbuf();
// }

#include "Renderer.hpp"
#include "Screen.hpp"
#include <iostream>

void Renderer::DrawScreen() {
  screen.clear();
  for (auto &obj : objpointer)
    obj->howDraw(screen);
  screen.WriteBuffer();
  std::cout << screen.printbuf.rdbuf();
}
