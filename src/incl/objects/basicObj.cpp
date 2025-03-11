#include "basicObj.hpp"
#include <cstddef>
#include <iostream>
#include <vector>
#include "../types/cell/ScreenCell.hpp"
#include "../general.hpp"
#include "../types/Point2D.hpp"

void basicObj::onFrame(float deltaT) {
  // std::cout << "running OnFrame\n";
  std::cout << Velocity.x << ' ' << Velocity.y << '\n';
  Velocity += dCosnt::GravV;
  applyVelocity();
}

void basicObj::applyVelocity() {
  std::cout << Origin.x << ' ' << Origin.y << "\nAddress: " << this << '\n';
  Origin += Velocity;
  // std::cout << "Applying Velocity\n";
}

void basicObj::howDraw(std::vector<ScreenCell> &framebuffer) {
  // std::cout << "HowDrawFunc\n";
  const float floorX{Origin.x - (int)Origin.x};
  const float floorY{Origin.x - (int)Origin.x};
  const int FrameBuffPos{(int)(Origin.x * Origin.y)};
  int out{0};
  if (floorX > 0.5) { out += 3; }
  if (floorY > 0.33333f) {
    if (floorY > 0.66666f) { out += 1; }
    out += 1;
  }

  auto &a((floorX > 0.5f) ? framebuffer[FrameBuffPos].left : framebuffer[FrameBuffPos].right);
  a.repres.show(1 << out);
  a.color.blend(color);
}