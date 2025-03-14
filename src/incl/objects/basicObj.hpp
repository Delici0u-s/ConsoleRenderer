#pragma once
#include "../types/Point3D.hpp"
#include "../types/color/color256.hpp"
#include <cstddef>
#include "../manager/Screen.hpp"

class basicObj {
public:
  Point3D Origin, Velocity;
  size_t ID;
  Color256 Color;
  float DespawnRad;

  basicObj(const Point3D &origin = {}, const Point3D &velocity = {}, const Color256 &color = {},
           const float despawnRadius = 0) :
      Origin{origin}, Velocity{velocity}, Color{color}, DespawnRad{despawnRadius} {
    static size_t maxID{0};
    ID = ++maxID;
  }
  virtual ~basicObj() = default;

  virtual void onFrame([[maybe_unused]] const float deltaT); // adds gravity to velocity and applys velocity be default
  virtual void howDraw(Screen &screen);                      // Draws origin by default
  // Virtual weglassn lol
};