#pragma once
#include "Renderer.hpp"
#include "../ext/consComm.hpp"
#include "../general.hpp"
#include <chrono>
#include <cstddef>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>
#include <queue> // New: For pending object queue
#include "../objects/DefaultObj.hpp"

class Handler {
private:
  Renderer renderer;
  bool run{false};
  void physicsRun();
  void RenderRunner();
  std::recursive_mutex renderMutex{};
  bool isInDespawnRange(const std::shared_ptr<DefaultObj> &obj);

  // Debug and FPS variables for rendering.
  double renderCurrentFPS{0.0};
  double renderMaxFPS{0.0};
  double renderMinFPS{1e9};
  unsigned long long totalObjectsCreated{0};

  // **New: Pending object queue** (to prevent modifying objpointer while iterating)
  std::queue<std::shared_ptr<DefaultObj>> pendingObjects;

public:
  std::vector<std::shared_ptr<DefaultObj>> objpointer{};
  float deltaT{0};
  unsigned int targetFrameRate{180};
  unsigned int ticks{100};  // physics ticks per second
  unsigned int subticks{5}; // substeps per tick

  Handler(unsigned int width, unsigned int height) : renderer(width, height, objpointer) {
    enableUtf8Console();
    std::cout << dcon::cmds::cursor::Hide << dcon::cmds::screen::Clear << dcon::cmds::cursor::ResetPosition;
    std::thread([&]() { physicsRun(); }).detach();
    std::thread([&]() { RenderRunner(); }).detach();
  }
  ~Handler() {
    Render(false);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << dcon::cmds::text::Reset << dcon::cmds::screen::Clear << dcon::cmds::cursor::ResetPosition
              << dcon::cmds::cursor::Show;
  }

  template <typename T, typename... Args>
  std::shared_ptr<T> AddObject(Args &&...args) {
    static_assert(std::is_base_of_v<DefaultObj, T>, "T must derive from DefaultObj");
    auto ptr = std::make_shared<T>(std::forward<Args>(args)...);
    {
      std::lock_guard<std::recursive_mutex> lg(renderMutex);
      pendingObjects.push(ptr); // **New: Use queue instead of direct insertion**
      totalObjectsCreated++;
    }
    return ptr;
  }
  template <typename T>
  std::shared_ptr<T> AddObject(T &&obj) {
    auto ptr = std::make_shared<std::decay_t<T>>(std::forward<T>(obj));
    {
      std::lock_guard<std::recursive_mutex> lg(renderMutex);
      pendingObjects.push(ptr); // **New: Use queue instead of direct insertion**
      totalObjectsCreated++;
    }
    return ptr;
  }

  void ProcessPendingObjects(); // **New: Method to process pending objects**

  void RemoveObject(size_t ID);
  std::shared_ptr<DefaultObj> GetObject(size_t ID);
  void Render(bool state = true) { run = state; }
};