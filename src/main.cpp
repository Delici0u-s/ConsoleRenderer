#include <chrono>
#include <iostream>
#include <thread>
#include "incl/general.hpp"
#include "incl/manager/Handler.hpp"
#include "incl/ext/consComm.hpp"
#include "incl/objects/basicObj.hpp"

int main() {
  // std::cout << "CreatingHandler\n";
  Handler H{20, 20};
  // std::cout << "CreatingBasicObj\n";
  basicObj OBJEKT;
  // std::cout << "AddingObj: " << OBJEKT.ID << '\n';
  H.AddObject(OBJEKT);
  // std::cout << "TriggeringRenderState\n";
  H.Render(true);
  std::this_thread::sleep_for(std::chrono::seconds(3));
  return 0;
}