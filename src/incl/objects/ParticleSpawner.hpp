#pragma once
#include "DefaultObj.hpp"
#include "../ext/random.h"
#include "Particle.hpp"
#include "../manager/Handler.hpp"

class ParticleSpawner : public DefaultObj {
public:
  float spawnInterval;
  float spawnAccumulator;
  Color256 particleColor;
  float particleLifetime;
  float particleDespawnRad;
  float velocityRange;
  Handler &handler;

  ParticleSpawner(const Point3D &origin, Handler &handler, float spawnInterval = 0.1f,
                  const Color256 &particleColor = {3, 252, 202, 255}, float particleLifetime = 3.0f,
                  float particleDespawnRad = 10.0f, float velocityRange = 0.02f, float SpawnerDespawnRange = 10.0f) :
      DefaultObj(origin, {0, 0, 0}, particleColor, SpawnerDespawnRange), spawnInterval(spawnInterval),
      spawnAccumulator(0.0f), particleColor(particleColor), particleLifetime(particleLifetime),
      particleDespawnRad(particleDespawnRad), velocityRange(velocityRange), handler(handler) {}

  void onFrame(float deltaT) override {
    spawnAccumulator += deltaT;

    while (spawnAccumulator >= spawnInterval) {
      // Generate random 2D velocity
      Point3D randomVel{static_cast<float>(Random::get(-100, 100)), static_cast<float>(Random::get(-100, 100)), 0.0f};
      randomVel *= 0.01 * velocityRange; // 0.01 because random::get is supposed to be -1 to 1

      // Directly add a new particle — AddObject now safely queues it
      handler.AddObject(Particle(Origin, randomVel, particleColor, particleDespawnRad, particleLifetime));

      spawnAccumulator -= spawnInterval;
    }
  }

  void howDraw([[maybe_unused]] Screen &screen) override {
    // Optional: visualize the spawner
    // try {
    //   auto &cell = screen.get(static_cast<unsigned int>(Origin.x), static_cast<unsigned int>(Origin.y));
    //   cell.repres.setChar("S", Origin.z);
    //   cell.color.blend(Color);
    // } catch (...) {}
  }
};
