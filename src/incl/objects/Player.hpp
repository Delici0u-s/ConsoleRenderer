#pragma once
#include "DefaultObj.hpp"
#include "../ext/key.hpp"
#include "Particle.hpp"
#include "src/incl/types/Point3D.hpp"

class Player : public DefaultObj {
public:
  Player(const Point3D &origin, const Color256 &color = {0, 255, 0, 255}) : DefaultObj(origin, {0, 0, 0}, color, 100) {}

  void onFrame(float deltaT) override {
    // Here you could check for key input to update the player's velocity or position.
    // For example:
    static Point3D Adder;
    Adder = {};
    if (dcon::Key::isKeyDown(dcon::Key::key::W)) Adder.y -= 1;
    if (dcon::Key::isKeyDown(dcon::Key::key::S)) Adder.y += 1;
    if (dcon::Key::isKeyDown(dcon::Key::key::A)) Adder.x -= 1;
    if (dcon::Key::isKeyDown(dcon::Key::key::D)) Adder.x += 1;
    Adder = Adder.normalized();
    Velocity += {Adder.x * 2.0f * deltaT, Adder.y * deltaT};
    Origin += Velocity;
    Velocity.linearLerpAssign({}, 0.03);
    // You can add more features (like shooting, collision, etc.) as needed.
  }

  void howDraw(Screen &screen) override { Particle{Origin, {0, 0}, Color, 0, 0}.howDraw(screen); }
};
