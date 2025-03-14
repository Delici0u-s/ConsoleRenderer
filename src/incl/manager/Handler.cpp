#include "Handler.hpp"
#include "Renderer.hpp"
#include "../ext/Timer.hpp"
#include "Screen.hpp"
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

void Handler::Runner() {
  Timer timer{};
#ifdef d_DEBUG
  Timer FrameT{};
  size_t outp{0}, FrameRateCounter{0};
#endif

  while (true) {
    if (run) {
      timer.reset();
      {
        std::lock_guard<std::mutex> LG{renderMutex};
        for (auto it = objpointer.begin(); it != objpointer.end();) {
          // Remove the object if it is off-screen or expired.
          if ((*it)->isExpired() || isInDespawnRange(*it)) it = objpointer.erase(it);
          else {
            (*it)->onFrame(deltaT);
            ++it;
          }
        }
        renderer.DrawScreen();
#ifdef d_DEBUG
        std::cout << dcon::cmds::screen::ClearLine << "Frames: " << outp << '/' << targetFrameRate
                  << " SumObjects: " << objpointer.size();
#endif
      }
      deltaT = timer.lap();
      static double frameDuration = 1.0 / targetFrameRate;
      if (deltaT < frameDuration) {
        auto sleepDuration = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::duration<double>(frameDuration - deltaT));
        std::this_thread::sleep_for(sleepDuration);
      }
#ifdef d_DEBUG
      ++FrameRateCounter;
      if (FrameT.elapsed() > 1) {
        outp = FrameRateCounter;
        FrameRateCounter = 0;
        FrameT.reset();
      }
#endif
    } else {
      std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
  }
}

// #include "Handler.hpp"
// #include "Renderer.hpp"
// #include "../ext/Timer.hpp"
// #include "Screen.hpp"
// #include <iostream>

// void Handler::RemoveObject(size_t ID) {
//   std::lock_guard<std::mutex> LG{renderMutex};
//   for (auto it = objpointer.begin(); it != objpointer.end(); ++it) {
//     if (it->getID() == ID) {
//       objpointer.erase(it);
//       return;
//     }
//   }
// }

// basicObj &Handler::GetObject(size_t ID) {
//   for (auto &obj : objpointer) {
//     if (obj.getID() == ID) return obj;
//   }
//   throw "ID not found";
// }

// bool Handler::isInDespawnRange(basicObj &obj) {
//   const Point3D &origin = obj.getOrigin();
//   float despawn = obj.getDespawnRad();
//   return origin.x < -despawn || origin.y < -despawn || origin.x > (renderer.getWidth() + despawn) ||
//          origin.y > (renderer.getHeight() + despawn);
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
//           if (isInDespawnRange(*it)) it = objpointer.erase(it);
//           else {
//             it->onFrame(deltaT);
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
