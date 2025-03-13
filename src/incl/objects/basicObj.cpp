#include "basicObj.hpp"
#include "../types/cell/ScreenCell.hpp"
#include "../general.hpp"
#include "../types/Point3D.hpp"
#include "src/incl/manager/Screen.hpp"

void basicObj::onFrame(const float deltaT) {
  Velocity += (dCosnt::GravV)*deltaT * 0.1;
  Origin += Velocity;
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
    auto &a{screen.get(static_cast<unsigned int>(Origin.x), static_cast<unsigned int>(Origin.y))};
    a.repres.show(1 << out);
    a.color.blend(Color);
  } catch (...) { ; }
}