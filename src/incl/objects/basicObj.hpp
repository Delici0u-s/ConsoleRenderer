#pragma once
#include "../types/Point2D.hpp"
#include "../types/color/color256.hpp"
#include <cstddef>
#include <vector>
#include "../types/cell/ScreenCell.hpp"

class basicObj {
public:
  Point2D Origin{0, 0}, Velocity{0, 0};
  size_t ID{0};
  Color256 color{255, 255, 255};
  float DespawnRad{0};
  int DrawPriority{0};

  void onFrame(float deltaT);
  void howDraw(std::vector<ScreenCell> &framebuffer);
  void applyVelocity();
  // virtual ~basicObj() = default;
};