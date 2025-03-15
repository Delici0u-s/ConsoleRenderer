#pragma once
#include "DefaultObj.hpp"
#include "../ext/random.h"
#include "Particle.hpp"           // Include Particle header
#include "../manager/Handler.hpp" // Include handler header to get the type

class ParticleSpawner : public DefaultObj {
public:
  float spawnInterval;
  float spawnAccumulator;
  Color256 particleColor;
  float particleLifetime;
  float particleDespawnRad;
  float velocityRange;
  // New member: pointer to the handler so we can add new particles.
  class Handler &handler;

  ParticleSpawner(const Point3D &origin, Handler &handler, float spawnInterval = 0.1f,
                  const Color256 &particleColor = {3, 252, 202, 255}, float particleLifetime = 3.0f,
                  float particleDespawnRad = 10.0f, float velocityRange = 0.02f) :
      DefaultObj(origin, {0, 0, 0}, particleColor, particleDespawnRad), spawnInterval(spawnInterval),
      spawnAccumulator(0.0f), particleColor(particleColor), particleLifetime(particleLifetime),
      particleDespawnRad(particleDespawnRad), velocityRange(velocityRange), handler(handler) {}

  void onFrame(float deltaT) override {
    Point3D randomVel{static_cast<float>(Random::get(-10, 10)) * velocityRange,
                      static_cast<float>(Random::get(-10, 10)) * velocityRange, 0.0f};
    handler.AddObject(Particle(Origin, randomVel, particleColor, particleDespawnRad, particleLifetime));
    // spawnAccumulator += deltaT;
    // // Spawn particles at fixed intervals
    // while (spawnAccumulator >= spawnInterval) {
    //   // Generate a random 2D velocity.
    //   Point3D randomVel{static_cast<float>(Random::get(-10, 10)) * velocityRange,
    //                     static_cast<float>(Random::get(-10, 10)) * velocityRange, 0.0f};
    //   // Use the handler to add a new Particle.
    //   handler.AddObject(Particle(Origin, randomVel, particleColor, particleDespawnRad, particleLifetime));
    //   spawnAccumulator -= spawnInterval;
    // }
  }

  void howDraw(Screen &screen) override {
    // Optionally, draw a marker for the spawner (e.g., an 'S')
    try {
      auto &cell = screen.get(static_cast<unsigned int>(Origin.x), static_cast<unsigned int>(Origin.y));
      cell.repres.setChar("*", Origin.z);
      cell.color.blend(Color);
    } catch (...) {
      // Ignore out-of-range drawing.
    }
  }
};
