#pragma once

#include "DefaultObj.hpp"
#include "src/incl/types/Point3D.hpp"

class backG : public DefaultObj {
public:
  Point3D Start, End;
  float Z;

  backG(const Color256 &color, const Point3D &end = {0, 0}, const Point3D &start = {0, 0}, const float z = -1,
        const Point3D origin = {}) : DefaultObj(origin, {}, color), Start(start), End{end}, Z{z} {}

  void onFrame(float deltaT) override;
  void howDraw(Screen &screen) override;
  constexpr float getWidth() const { return (End.x >= Start.x) ? (End.x - Start.x) : (Start.x - End.x); }
  constexpr float getHeight() const { return (End.y >= Start.y) ? (End.y - Start.y) : (Start.y - End.y); }
};
