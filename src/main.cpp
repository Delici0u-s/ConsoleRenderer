#include <chrono>
#include <iostream>
#include <thread>
#include "incl/general.hpp"
#include "incl/manager/Handler.hpp"
#include "incl/ext/consComm.hpp"
#include "incl/objects/basicObj.hpp"

int main() {
  Handler H{40, 40};

  basicObj OBJEKT;
  OBJEKT.Velocity = {0.01, -0.02};
  OBJEKT.Origin = {10, 10};
  H.AddObject(OBJEKT);

  basicObj OBJEKT1;
  OBJEKT1.Velocity = {-0.01, -0.02};
  OBJEKT1.Origin = {20, 10};
  OBJEKT1.color = {255, 0, 0};
  H.AddObject(OBJEKT1);

  H.Render(true);

  std::this_thread::sleep_for(std::chrono::seconds(9));
  return 0;
}