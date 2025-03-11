#include "Handler.hpp"
#include "Renderer.hpp"
#include "../objects/basicObj.hpp"
#include <chrono>
#include <cstddef>
#include <mutex>
#include <thread>
#include "../ext/Timer.h"
#include <iostream>

void Handler::AddObject(const basicObj &Object) {
  //   std::lock_guard LG{renderMutex};
  objpointer.push_back(Object);
}
void Handler::RemoveObject(size_t ID) {
  std::lock_guard LG{renderMutex};
  for (size_t i{0}; i < objpointer.size(); ++i)
    if (objpointer[i].ID == ID) objpointer.erase(objpointer.begin() + i);
}

void Handler::Runner() {
  Timer timer{};
  while (true) {
    std::lock_guard LG{renderMutex};
    // std::cout << "inWhileLoop\n";
    if (run) {
      //   std::cout << "Attempring Frame\n";
      timer.reset();

      {
        // std::cout << "Runninf OnFramelogic: \n";
        for (auto &i : objpointer) {
          //   std::cout << i.ID << '\n';
          std::cout << "\nOriginal:\n" << i.Origin.x << ' ' << i.Origin.x << '\n';
          std::cout << i.Velocity.x << ' ' << i.Velocity.x << "\nAddress: " << &i << "\nonFrame: \n";
          i.onFrame(deltaT);
        }

        // std::cout << "Running DrawScreen: \n";
        // renderer.DrawScreen();
      }

      deltaT = timer.delapsed();
      if (deltaT < (1.0 / targetFrameRate))
        std::this_thread::sleep_for(std::chrono::milliseconds{1000 * (int)((1.0 / targetFrameRate) - deltaT)});
      //   std::cout << "Done Frame\n";
    } else {
      //   std::cout << "AttemptingSleep";
      std::this_thread::sleep_for(std::chrono::milliseconds(30));
      //   std::cout << "endSleep";
    }
    // std::cout << "EndLoop\n";
  }
}