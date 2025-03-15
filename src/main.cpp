#include "incl/manager/Handler.hpp"
#include "incl/objects/Particle.hpp"
#include "incl/objects/text.hpp"
#include "incl/types/Point3D.hpp"
#include "incl/types/color/color256.hpp"
#include "incl/ext/random.h"
#include "incl/ext/key.hpp"
#include <chrono>
#include <thread>
#include "incl/objects/BackgroundS.hpp"

// suggested to stay 180 x 40
#define WIDTH 160
#define HEIGHT 40

int main() {
  Handler H{WIDTH, HEIGHT};
  H.Render(true);

  auto a{H.AddObject(backgroundS{{255, 0, 0}, {10, 5, 1}})};
  H.AddObject(text{"Hello\nworld\nund Fritz!",
                   text::alignment::left,
                   {10, 10, 10},
                   {},
                   {255, 255, 255, 255},
                   {100, 100, 100, 40},
                   -1});

  float x = WIDTH / 2.0f, y = HEIGHT / 2.0f;
  Point3D addTo;

  // H.AddObject(backG{{255, 0, 0}, {10, 10}});

  while (true) {
    // Create and add a Particle with a lifetime of 3 seconds.
    H.AddObject(Particle{Point3D{x, y},
                         Point3D{static_cast<float>(Random::get(-20, 20) * 0.001f) + addTo.x,
                                 static_cast<float>(Random::get(-20, 20) * 0.001f) + addTo.y},
                         Color256{3, 252, 202, 255}, 10, 0.3f});

    a->Origin.linearLerpAssign({x - a->getWidth() / 2, y - a->getHeight() / 2}, 0.05);

    std::this_thread::sleep_for(std::chrono::milliseconds(30));

    addTo = 0;
    if (dcon::Key::isKeyDown(dcon::Key::key::ESCAPE)) break;
    if (dcon::Key::isKeyDown(dcon::Key::key::W)) {
      y -= 0.5f;
      addTo.y -= 0.05f;
    }
    if (dcon::Key::isKeyDown(dcon::Key::key::S)) {
      y += 0.5f;
      addTo.y += 0.05f;
    }
    if (dcon::Key::isKeyDown(dcon::Key::key::A)) {
      x -= 1.0f;
      addTo.x -= 0.1f;
    }
    if (dcon::Key::isKeyDown(dcon::Key::key::D)) {
      x += 1.0f;
      addTo.x += 0.1f;
    }
  }

  return 0;
}
