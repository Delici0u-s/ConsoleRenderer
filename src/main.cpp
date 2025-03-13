#include <chrono>
#include <thread>
#include "incl/general.hpp"
#include "incl/manager/Handler.hpp"
#include "incl/objects/basicObj.hpp"
#include "incl/ext/random.h"
#include "incl/ext/key.hpp"
#include "incl/types/Point3D.hpp"

#define WIDTH 160
#define HEIGHT 40

int main() {
  Handler H{WIDTH, HEIGHT};

  H.Render(true);
  float x{WIDTH / 2.0}, y{HEIGHT / 2.0};
  Point3D addTo;

  while (true) {
    // Colored
    H.AddObject({{x, y},
                 {
                     static_cast<float>(Random::get(-20, 20) * 0.002) + addTo.x,
                     static_cast<float>(Random::get(-20, 20) * 0.002) + addTo.y,
                 },
                 {
                     Random::get<unsigned char>(0x00, 0xFF),
                     Random::get<unsigned char>(0x00, 0xFF),
                     Random::get<unsigned char>(0x00, 0xFF),
                 },
                 10});
    // Only white
    // H.AddObject({{x, y},
    //              {static_cast<float>(Random::get(-20, 20) * 0.001) + addTo.x,
    //               static_cast<float>(Random::get(-20, 20) * 0.001) + addTo.y},
    //              {255, 255, 255, 255},
    //              10});
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    addTo = 0;
    if (dcon::Key::isKeyDown(dcon::Key::key::ESCAPE)) break;
    if (dcon::Key::isKeyDown(dcon::Key::key::W)) y -= 0.5, addTo.y -= 0.05;
    if (dcon::Key::isKeyDown(dcon::Key::key::S)) y += 0.5, addTo.y += 0.05;
    if (dcon::Key::isKeyDown(dcon::Key::key::A)) x -= 1, addTo.x -= 0.1;
    if (dcon::Key::isKeyDown(dcon::Key::key::D)) x += 1, addTo.x += 0.1;
  }

  return 0;
}