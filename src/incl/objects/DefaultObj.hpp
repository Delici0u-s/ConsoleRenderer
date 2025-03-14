#pragma once

#include "../types/Point3D.hpp"
#include "../types/color/color256.hpp"
#include "../manager/Screen.hpp"
#include <cstddef>

class DefaultObj {
public:
  Point3D Origin, Velocity;
  Color256 Color;
  float DespawnRad;
  size_t ID;

  DefaultObj(const Point3D &origin = {}, const Point3D &velocity = {}, const Color256 &color = {},
             float despawnRad = 0) : Origin(origin), Velocity(velocity), Color(color), DespawnRad(despawnRad) {
    static size_t maxID = 0;
    ID = ++maxID;
  }
  virtual ~DefaultObj() = default;

  // Update the object (e.g. physics, lifetime, etc.)
  virtual void onFrame(float deltaT) = 0;

  // Draw the object on the screen.
  virtual void howDraw(Screen &screen) = 0;

  // By default, an object does not expire.
  virtual bool isExpired() const { return false; }
};
