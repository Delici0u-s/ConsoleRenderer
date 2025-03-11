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

void Handler::AddObject(const basicObj &Object) {
  //   std::lock_guard LG{renderMutex};
  objpointer.push_back(Object);
}
void Handler::RemoveObject(size_t ID) {
  std::lock_guard LG{renderMutex};
  for (size_t i{0}; i < objpointer.size(); ++i)
    if (objpointer[i].ID == ID) objpointer.erase(objpointer.begin() + i);
}
basicObj &Handler::GetObject(size_t ID) {
  for (auto &i : objpointer)
    if (i.ID == ID) return i;
  throw "ID not found";
}

void Handler::Runner() {
  Timer timer{};
  while (true) {
    // std::cout << "inWhileLoop\n";
    if (run) {
      //   std::cout << "Attempring Frame\n";
      timer.reset();

      {
        std::lock_guard LG{renderMutex};
        // std::cout << "Runninf OnFramelogic: \n";
        for (auto &i : objpointer) {
          //   std::cout << i.ID << '\n';
          // std::cout << "Original:\n\tAddressi: \n\t\tObj: " << &i << "\n\t\tObjOrigin: " << &(i.Origin)
          //           << "\n\t\t\tx: " << &(i.Origin.x) << "\n\t\t\ty: " << &(i.Origin.y)
          //           << "\n\t\tVelocity : " << &(i.Velocity) << "\n\t\t\tx: " << &(i.Velocity.x)
          //           << "\n\t\t\ty: " << &(i.Velocity.y);
          // std::cout << "\n\tValues: \n\t\tOrigin  : " << i.Origin.x << ' ' << i.Origin.y
          //           << "\n\t\tVelocity: " << i.Velocity.x << ' ' << i.Velocity.y << '\n';
          i.onFrame(deltaT);
        }

        // std::cout << "Running DrawScreen: \n";
        renderer.DrawScreen();
        // std::cout << dcon::cmds::screen::ClearLine << objpointer[0].Origin.x << ' ' << objpointer[0].Origin.y << "  "
        //           << (int)objpointer[0].Origin.x << ' ' << (int)objpointer[0].Origin.y * 40 <<
        //           dcon::cmds::cursor::Up;
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