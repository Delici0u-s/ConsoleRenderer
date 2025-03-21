#pragma once

#include "DefaultObj.hpp"
#include "../types/Point3D.hpp"

class backgroundS : public DefaultObj {
public:
  Point3D Start, End;

  backgroundS(const Color256 &color, const Point3D &end = {0, 0}, const Point3D &start = {0, 0},
              const Point3D origin = {}, float despawnRad = 0) :
      DefaultObj(origin, {}, color, despawnRad), Start(start), End{end} {}

  void onFrame(float deltaT) override;
  void howDraw(Screen &screen) override;
  constexpr float getWidth() const { return (End.x >= Start.x) ? (End.x - Start.x) : (Start.x - End.x); }
  constexpr float getHeight() const { return (End.y >= Start.y) ? (End.y - Start.y) : (Start.y - End.y); }
};
