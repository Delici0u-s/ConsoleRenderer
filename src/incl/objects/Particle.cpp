#include "Particle.hpp"
#include "../types/cell/ScreenCell.hpp"
#include "../general.hpp"

Particle::Particle(const Point3D &origin, const Point3D &velocity, const Color256 &color, float despawnRad,
                   float lifetime) : DefaultObj(origin, velocity, color, despawnRad), lifetime(lifetime) {}

void Particle::onFrame(float deltaT) {
  // Decrement lifetime.
  lifetime -= deltaT;
  // Update position (applying gravity, for example).
  Velocity += dCosnt::GravV * deltaT * 0.1f;
  Origin += Velocity;
}

void Particle::howDraw(Screen &screen) {
  // A simple way to choose a representation based on fractional parts of the position.
  const float floorX = Origin.x - static_cast<int>(Origin.x);
  const float floorY = Origin.y - static_cast<int>(Origin.y);
  int out = 0;
  if (floorX > 0.5f) out += 3;
  if (floorY > 0.75f) out = (out == 3) ? 7 : 6;
  else if (floorY > 0.5f) out += 2;
  else out += 1;

  try {
    auto &cell = screen.get(static_cast<unsigned int>(Origin.x), static_cast<unsigned int>(Origin.y));
    cell.repres.show(1 << out);
    cell.color.blend(Color);
  } catch (...) {
    // Ignore out-of-range drawing.
  }
}

bool Particle::isExpired() const { return lifetime <= 0; }
