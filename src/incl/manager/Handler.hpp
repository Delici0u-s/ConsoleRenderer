#pragma once
#include "Renderer.hpp"
#include "../objects/basicObj.hpp"
#include "../general.hpp"
#include "src/incl/ext/consComm.hpp"
#include <chrono>
#include <cstddef>
#include <thread>
#include <mutex>

class Handler {
private:
  Renderer renderer;
  bool run{false};

  void Runner();
  std::mutex renderMutex{};

  bool isInDespawnRange(basicObj &obj);

public:
  std::vector<basicObj> objpointer{};
  float deltaT{0};
  // Will be vsync capped because damn console
  unsigned int targetFrameRate{180};
  Handler(unsigned int width, unsigned int height) : renderer(width, height, objpointer) {
    enableUtf8Console();
    std::cout << dcon::cmds::cursor::Hide << dcon::cmds::screen::Clear << dcon::cmds::cursor::ResetPosition;

    std::thread([&]() { Runner(); }).detach();
  }
  ~Handler() {
    Render(false);
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // sleep so async printscreen doesnt prints again
    std::cout << dcon::cmds::text::Reset << dcon::cmds::screen::Clear << dcon::cmds::cursor::ResetPosition
              << dcon::cmds::cursor::Show;
  }

  basicObj &AddObject(const basicObj &Object);
  void RemoveObject(size_t ID);
  basicObj &GetObject(size_t ID);
  void Render(bool state = true) { run = state; }
};