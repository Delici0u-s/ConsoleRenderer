#pragma once
#include "Renderer.hpp"
#include "../objects/basicObj.hpp"
#include "../general.hpp"
#include "src/incl/ext/consComm.hpp"
#include <cstddef>
#include <thread>
#include <mutex>

class Handler {
private:
  Renderer renderer;
  bool run{false};

  void Runner();
  std::mutex renderMutex{};

public:
  std::vector<basicObj> objpointer{};
  float deltaT{0};
  unsigned int targetFrameRate{7};
  Handler(int width, int size) : renderer(width, size, objpointer) {
    enableUtf8Console();
    std::cout << dcon::cmds::cursor::Hide << '\n';
    std::thread([&]() { Runner(); }).detach();
  }
  ~Handler() { std::cout << dcon::cmds::cursor::Show << dcon::cmds::text::Reset; }

  void AddObject(const basicObj &Object);
  void RemoveObject(size_t ID);
  void Render(bool state = true) { run = state; }
};