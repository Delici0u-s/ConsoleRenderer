#include "Handler.hpp"
#include "Renderer.hpp"
#include "../objects/basicObj.hpp"
#include <chrono>
#include <cstddef>
#include <mutex>
#include <thread>
#include "../ext/Timer.h"
#include "Screen.hpp"
#include "src/incl/ext/consComm.hpp"
#include <iostream>

basicObj &Handler::AddObject(const basicObj &Object) {
  //   std::lock_guard LG{renderMutex};
  objpointer.push_back(Object);
  return objpointer.back();
}
void Handler::RemoveObject(size_t ID) {
  // std::lock_guard LG{renderMutex};
  for (size_t i{0}; i < objpointer.size(); ++i)
    if (objpointer[i].ID == ID) objpointer.erase(objpointer.begin() + i);
}

basicObj &Handler::GetObject(size_t ID) {
  for (auto &i : objpointer)
    if (i.ID == ID) return i;
  throw "ID not found";
}

bool Handler::isInDespawnRange(basicObj &obj) {
  return obj.Origin.x < -obj.DespawnRad || obj.Origin.y < -obj.DespawnRad ||
         obj.Origin.x > (renderer.getWidth() + obj.DespawnRad) ||
         obj.Origin.y > (renderer.getHeight() + obj.DespawnRad);
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
        std::lock_guard LG{renderMutex};
        for (auto &i : objpointer) {
          // if object is out of render range despawn it
          if (isInDespawnRange(i)) {
            RemoveObject(i.ID);
            continue;
          }
          i.onFrame(deltaT);
        }

        renderer.DrawScreen();
#ifdef d_DEBUG
        std::cout << dcon::cmds::screen::ClearLine << "Frames: " << outp << '/' << targetFrameRate
                  << " SumObjects: " << objpointer.size();
#endif
      }

      deltaT = timer.delapsed();
      if (deltaT < (1.0 / targetFrameRate))
        std::this_thread::sleep_for(std::chrono::milliseconds{1000 * (int)((1.0 / targetFrameRate) - deltaT)});
#ifdef d_DEBUG
      ++FrameRateCounter;
      if (FrameT.delapsed() > 1) {
        outp = FrameRateCounter;
        FrameRateCounter = 0;
        FrameT.reset();
      }
#endif
      //   std::cout << "Done Frame\n";
    } else {
      //   std::cout << "AttemptingSleep";
      std::this_thread::sleep_for(std::chrono::milliseconds(30));
      //   std::cout << "endSleep";
    }
    // std::cout << "EndLoop\n";
  }
}