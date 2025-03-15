#pragma once
#include "DefaultObj.hpp"
#include "../ext/key.hpp"
#include "Particle.hpp"

class Player : public DefaultObj {
public:
  Player(const Point3D &origin, const Color256 &color = {0, 255, 0, 255}) : DefaultObj(origin, {0, 0, 0}, color) {}

  void onFrame(float deltaT) override {
    // Here you could check for key input to update the player's velocity or position.
    // For example:
    if (dcon::Key::isKeyDown(dcon::Key::key::W)) Origin.y -= 5.0f * deltaT;
    if (dcon::Key::isKeyDown(dcon::Key::key::S)) Origin.y += 5.0f * deltaT;
    if (dcon::Key::isKeyDown(dcon::Key::key::A)) Origin.x -= 10.0f * deltaT;
    if (dcon::Key::isKeyDown(dcon::Key::key::D)) Origin.x += 10.0f * deltaT;
    // You can add more features (like shooting, collision, etc.) as needed.
  }

  void howDraw(Screen &screen) override {
    // Draw a 'P' at the player's position.
    Particle{Origin, {0, 0}, Color, 0, 0}.howDraw(screen);
    // try {
    //   auto &cell = screen.get(static_cast<unsigned int>(Origin.x), static_cast<unsigned int>(Origin.y));
    //   cell.repres.setChar("P", Origin.z);
    //   cell.color.blend(Color);
    // } catch (...) {
    //   // Handle out-of-range errors.
    // }
  }
};
