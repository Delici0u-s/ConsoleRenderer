#include "basicObj.hpp"
#include <cstddef>
#include <iostream>
#include <vector>
#include "../types/cell/ScreenCell.hpp"
#include "../general.hpp"
#include "../types/Point2D.hpp"
#include "src/incl/manager/Screen.hpp"

void basicObj::onFrame(float deltaT) {
  // std::cout << "running OnFrame\n";
  // std::cout << Velocity.x << ' ' << Velocity.y << '\n';
  Velocity += (dCosnt::GravV)*deltaT * 0.01;
  applyVelocity();
}

void basicObj::applyVelocity() {
  // std::cout << Origin.x << ' ' << Origin.y << "\nAddress: " << this << '\n';
  Origin += Velocity;
  // std::cout << "Applying Velocity\n";
}

void basicObj::howDraw(Screen &screen) {
  // std::cout << "HowDrawFunc\n";
  const float floorX{Origin.x - (int)Origin.x};
  const float floorY{Origin.y - (int)Origin.y};
  int out{0};
  if (floorX >= 0.75f || (floorX >= 0.25f && floorX <= 0.5f)) out += 3;
  if (floorY > 0.3333f) {
    if (floorY > 0.6666f) ++out;
    ++out;
  }

  try {
    auto &b{screen.get(static_cast<unsigned int>(Origin.x), static_cast<unsigned int>(Origin.y))};
    auto &a((floorX < 0.5f) ? b.left : b.right);
    a.repres.show(1 << out);
    a.color.blend(color);
  } catch (...) {}
}