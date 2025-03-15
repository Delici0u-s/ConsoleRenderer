
#include "Handler.hpp"
#include "Renderer.hpp"
#include "../ext/Timer.hpp"
#include "Screen.hpp"
#include "src/incl/ext/consComm.hpp"
#include <iostream>

void Handler::RemoveObject(size_t ID) {
  // std::lock_guard<std::mutex> LG{renderMutex};
  for (auto it = objpointer.begin(); it != objpointer.end(); ++it) {
    if ((*it)->ID == ID) {
      objpointer.erase(it);
      return;
    }
  }
}

std::shared_ptr<DefaultObj> Handler::GetObject(size_t ID) {
  for (auto &obj : objpointer) {
    if (obj->ID == ID) return obj;
  }
  throw "ID not found";
}

bool Handler::isInDespawnRange(const std::shared_ptr<DefaultObj> &obj) {
  const Point3D &origin = obj->Origin;
  float despawn = obj->DespawnRad;
  return origin.x < -despawn || origin.y < -despawn || origin.x > (renderer.getWidth() + despawn) ||
         origin.y > (renderer.getHeight() + despawn);
}

void Handler::physicsRun() {
  Timer timer{};
  double accumulator = 0.0;
  // dt_tick is the intended physics tick (e.g. 1/100 sec).
  const double dt_tick = 1.0 / ticks;
  // dt_sub is the substep duration.
  const double dt_sub = dt_tick / subticks;

  while (true) {
    if (run) {
      // Get elapsed time since last loop.
      double frameTime = timer.lap();
      accumulator += frameTime;

      // Process physics in fixed dt_tick increments.
      while (accumulator >= dt_tick) {
        // For each full physics tick, perform the defined number of substeps.
        for (unsigned int s = 0; s < subticks; ++s) {
          std::lock_guard<std::mutex> LG{renderMutex};
          for (auto it = objpointer.begin(); it != objpointer.end();) {
            if (*it && ((*it)->isExpired() || isInDespawnRange(*it))) {
              it = objpointer.erase(it);
            } else {
              if (*it) (*it)->onFrame(static_cast<float>(dt_sub));
              ++it;
            }
          }
        }
        accumulator -= dt_tick; // Remove exactly one tick's worth of time.
      }

      // Optionally sleep if the elapsed frameTime is less than dt_tick.
      if (frameTime < dt_tick) {
        auto sleepDuration =
            std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::duration<double>(dt_tick - frameTime));
        std::this_thread::sleep_for(sleepDuration);
      }
    } else {
      std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
  }
}

// void Handler::physicsRun() {
//   Timer timer{};
//   double accumulator = 0.0; // dt_sub is the fixed time step for each subframe.
//   const double dt_sub = 1.0 / (ticks * subticks);

//   while (true) {
//     if (run) { // Measure how much time has elapsed since last loop.
//       double frameTime = timer.lap();
//       accumulator += frameTime;

//       // Process physics in fixed dt_sub increments.
//       while (accumulator >= dt_sub) {
//         {
//           std::lock_guard<std::mutex> LG{renderMutex};
//           // Iterate over objects and update or remove them.
//           for (auto it = objpointer.begin(); it != objpointer.end();) {
//             if (*it && (((*it)->isExpired()) || isInDespawnRange(*it))) {
//               // Remove expired/out-of-bound object.
//               it = objpointer.erase(it);
//             } else {
//               // Update object with fixed subframe dt.
//               if (*it) (*it)->onFrame(static_cast<float>(dt_sub));
//               ++it;
//             }
//           }
//         }
//         accumulator -= dt_sub;
//       }

//       // Sleep a little if needed so that physics don't run too fast.
//       double targetPhysicsFrame = 1.0 / ticks;
//       if (frameTime < targetPhysicsFrame) {
//         auto sleepDuration = std::chrono::duration_cast<std::chrono::milliseconds>(
//             std::chrono::duration<double>(targetPhysicsFrame - frameTime));
//         std::this_thread::sleep_for(sleepDuration);
//       }
//     } else {
//       std::this_thread::sleep_for(std::chrono::milliseconds(30));
//     }
//   }
// }

void Handler::RenderRunner() {
  Timer frameTimer{};
  Timer fpsTimer{};
  int frameCount = 0;

  while (true) {
    if (run) {
      static const double targetFrameDuration = 1.0 / targetFrameRate;

      // Draw the screen.
      renderer.DrawScreen();
      frameCount++;

      // Update FPS statistics every second.
      double elapsedFps = fpsTimer.elapsed();
      if (elapsedFps >= 1.0) {
        renderCurrentFPS = frameCount / elapsedFps;
        if (renderCurrentFPS > renderMaxFPS) renderMaxFPS = renderCurrentFPS;
        if (renderCurrentFPS < renderMinFPS) renderMinFPS = renderCurrentFPS;
        frameCount = 0;
        fpsTimer.reset();
      }

#ifdef d_DEBUG // Print a debug line with desired information.
      std::cout << dcon::cmds::screen::ClearLine << "Target FPS: " << targetFrameRate
                << " | Current FPS: " << renderCurrentFPS << " | Max FPS: " << renderMaxFPS
                << " | Min FPS: " << renderMinFPS << " | Total Objects Created: " << totalObjectsCreated
                << " | Active Objects: " << objpointer.size();
#endif

      double renderTime = frameTimer.lap();
      if (renderTime < targetFrameDuration) {
        auto sleepDuration = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::duration<double>(targetFrameDuration - renderTime));
        std::this_thread::sleep_for(sleepDuration);
      }
    } else {
      std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
  }
}

// void Handler::RenderRunner() {
//   Timer timer{};
//   float tim{0};
// #ifdef d_DEBUG
// #endif

//   while (true) {
//     if (run) {
//       static double frameDuration = 1.0 / targetFrameRate;

//       renderer.DrawScreen();
// #ifdef d_DEBUG
//       std::cout << dcon::cmds::screen::ClearLine << "TotalObjects: " << objpointer.size();
// #endif

//       tim = timer.lap();
//       if (tim < frameDuration) {
//         auto sleepDuration =
//             std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::duration<double>(frameDuration -
//             tim));
//         std::this_thread::sleep_for(sleepDuration);
//       }

//     } else std::this_thread::sleep_for(std::chrono::milliseconds(30));
//   }
// }

// void Handler::physicsRun() {
//   Timer timer{};

//   while (true) {
//     if (run) {
//       static double frameDuration = 1.0 / ticks;

//       {
//         std::lock_guard<std::mutex> LG{renderMutex};
//         for (auto &i : objpointer) {
//           if (i) {
//             if (i->isExpired() || isInDespawnRange(i)) RemoveObject(i->ID);
//             else i->onFrame(deltaT);
//           }
//         }
//       }

//       deltaT = timer.lap();
//       if (deltaT < frameDuration) {
//         auto sleepDuration = std::chrono::duration_cast<std::chrono::milliseconds>(
//             std::chrono::duration<double>(frameDuration - deltaT));
//         std::this_thread::sleep_for(sleepDuration);
//       }
//     } else std::this_thread::sleep_for(std::chrono::milliseconds(30));
//   }
// }

// void Handler::Runner() {
//   Timer timer{};
// #ifdef d_DEBUG
//   Timer FrameT{};
//   size_t outp{0}, FrameRateCounter{0};
// #endif

//   while (true) {
//     if (run) {
//       timer.reset();
//       {
//         std::lock_guard<std::mutex> LG{renderMutex};
//         for (auto it = objpointer.begin(); it != objpointer.end();) {
//           // Remove the object if it is off-screen or expired.
//           if ((*it)->isExpired() || isInDespawnRange(*it)) it = objpointer.erase(it);
//           else {
//             (*it)->onFrame(deltaT);
//             ++it;
//           }
//         }
//         renderer.DrawScreen();
// #ifdef d_DEBUG
//         std::cout << dcon::cmds::screen::ClearLine << "Frames: " << outp << '/' << targetFrameRate
//                   << " SumObjects: " << objpointer.size();
// #endif
//       }
//       deltaT = timer.lap();
//       static double frameDuration = 1.0 / targetFrameRate;
//       if (deltaT < frameDuration) {
//         auto sleepDuration = std::chrono::duration_cast<std::chrono::milliseconds>(
//             std::chrono::duration<double>(frameDuration - deltaT));
//         std::this_thread::sleep_for(sleepDuration);
//       }
// #ifdef d_DEBUG
//       ++FrameRateCounter;
//       if (FrameT.elapsed() > 1) {
//         outp = FrameRateCounter;
//         FrameRateCounter = 0;
//         FrameT.reset();
//       }
// #endif
//     } else {
//       std::this_thread::sleep_for(std::chrono::milliseconds(30));
//     }
//   }
// }
