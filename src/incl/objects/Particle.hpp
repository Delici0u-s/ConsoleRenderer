#pragma once

#include "DefaultObj.hpp"

class Particle : public DefaultObj {
public:
  float lifetime; // Lifetime in seconds

  Particle(const Point3D &origin, const Point3D &velocity, const Color256 &color, float despawnRad, float lifetime);

  void onFrame(float deltaT) override;
  void howDraw(Screen &screen) override;
  bool isExpired() const override;
};
