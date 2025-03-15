#include "incl/manager/Handler.hpp"
#include "incl/objects/Particle.hpp"
#include "incl/objects/text.hpp"
#include "incl/objects/Player.hpp"          // New header for the player
#include "incl/objects/ParticleSpawner.hpp" // New header for the particle spawner
#include "incl/types/Point3D.hpp"
#include "incl/types/color/color256.hpp"
#include "incl/ext/random.h"
#include "incl/ext/key.hpp"
#include <algorithm>
#include <chrono>
#include <thread>
#include "incl/objects/BackgroundS.hpp"

// Suggested screen dimensions (e.g., 180x40)
#define WIDTH 180
#define HEIGHT 40

int main() {
  Handler H{WIDTH, HEIGHT};
  H.Render(true);

  // Create a background object (if needed)
  auto bg = H.AddObject(backgroundS{{255, 0, 0}, {4, 2, 1}});

  // Create a sample text object for additional visual feedback.
  auto txt{H.AddObject(text{
      "Run Away From\nTHE CUBEEE!!!",
      text::alignment::center,
      {WIDTH / 2.0f - 6, 3, 0},
      {},
      {255, 255, 255, 255},
      -1,
      {100, 100, 100, 40},
  })};

  H.AddObject(text{
      "Controls\nUP: W\nLEFT: A\nRIGHT: D\nDOWN: S\nExit: ESC",
      text::alignment::right,
      {WIDTH - 9, 0, 100},
      {},
      {"FEE7E7"},
  });
  H.AddObject(backgroundS({"101820"}, {WIDTH, 6}, {WIDTH - 9, 0}, {0, 0, 10}));

  // Set initial player position at the center of the screen.
  float playerX = WIDTH / 2.0f;
  float playerY = HEIGHT / 2.0f;
  Point3D playerOrigin{playerX, playerY, 0};

  // Create the particle spawner, with its origin initially set to the player's origin.
  auto spawner = H.AddObject(ParticleSpawner({20, 10}, H,
                                             0.01f,              // spawn interval in seconds
                                             {3, 252, 202, 255}, // particle color
                                             0.5f,               // particle lifetime
                                             10.0f,              // despawn radius
                                             0.02f, 100));       // velocity range
  H.AddObject(Particle({40, 5}, {}, {255, 255, 255}, 0, 3.0f));
  H.AddObject(Particle({40.5, 5}, {}, {255, 255, 255}, 0, 3.0f));
  H.AddObject(Particle({41, 5}, {}, {255, 255, 255}, 0, 3.0f));
  H.AddObject(Particle({41.5, 5}, {}, {255, 255, 255}, 0, 3.0f));

  // Create the player object.
  auto player = H.AddObject(Player(playerOrigin, {0, 255, 0}));

  // Main loop: update the spawner's origin to follow the player's position.
  while (true) {
    // The player's onFrame handles its own movement via key input.
    // Update the spawner's origin so particles spawn at the player position.

    // player->Origin.x = std::clamp(player->Origin.x, -5.0f, 2.0f + WIDTH);
    // player->Origin.y = std::clamp(player->Origin.y, -5.0f, 2.0f + HEIGHT);
    player->Origin.x = std::clamp(player->Origin.x, .0f, .0f + WIDTH);
    player->Origin.y = std::clamp(player->Origin.y, .0f, .0f + HEIGHT);

    spawner->Origin = player->Origin;
    bg->Origin.linearLerpAssign(player->Origin - Point3D(bg->getWidth() / 2.0f, bg->getHeight() / 2.0f, 0), 0.03);

    std::this_thread::sleep_for(std::chrono::milliseconds(30));

    if (dcon::Key::isKeyDown(dcon::Key::key::ESCAPE)) break;
  }
}

// #include "incl/manager/Handler.hpp"
// #include "incl/objects/Particle.hpp"
// #include "incl/objects/text.hpp"
// #include "incl/types/Point3D.hpp"
// #include "incl/types/color/color256.hpp"
// #include "incl/ext/random.h"
// #include "incl/ext/key.hpp"
// #include <chrono>
// #include <thread>
// #include "incl/objects/BackgroundS.hpp"

// // suggested to stay 180 x 40
// #define WIDTH 180
// #define HEIGHT 40

// int main() {
//   Handler H{WIDTH, HEIGHT};
//   H.Render(true);

//   auto a{H.AddObject(backgroundS{{255, 0, 0}, {10, 5, 1}})};
//   H.AddObject(text{"Hello\nworld\nund Fritz!",
//                    text::alignment::left,
//                    {10, 10, 10},
//                    {},
//                    {255, 255, 255, 255},
//                    {100, 100, 100, 40},
//                    -1});

//   float x = WIDTH / 2.0f, y = HEIGHT / 2.0f;
//   Point3D addTo;

//   // H.AddObject(backG{{255, 0, 0}, {10, 10}});

//   while (true) {
//     // Create and add a Particle with a lifetime of 3 seconds.
//     H.AddObject(Particle{Point3D{x, y},
//                          Point3D{static_cast<float>(Random::get(-20, 20) * 0.001f) + addTo.x,
//                                  static_cast<float>(Random::get(-20, 20) * 0.001f) + addTo.y},
//                          Color256{3, 252, 202, 255}, 10, 3.0f});

//     a->Origin.linearLerpAssign({x - a->getWidth() / 2, y - a->getHeight() / 2}, 0.05);

//     std::this_thread::sleep_for(std::chrono::milliseconds(30));

//     addTo = 0;
//     if (dcon::Key::isKeyDown(dcon::Key::key::ESCAPE)) break;
//     if (dcon::Key::isKeyDown(dcon::Key::key::W)) {
//       y -= 0.5f;
//       addTo.y -= 0.005f;
//     }
//     if (dcon::Key::isKeyDown(dcon::Key::key::S)) {
//       y += 0.5f;
//       addTo.y += 0.005f;
//     }
//     if (dcon::Key::isKeyDown(dcon::Key::key::A)) {
//       x -= 1.0f;
//       addTo.x -= 0.01f;
//     }
//     if (dcon::Key::isKeyDown(dcon::Key::key::D)) {
//       x += 1.0f;
//       addTo.x += 0.01f;
//     }
//   }

//   return 0;
// }
