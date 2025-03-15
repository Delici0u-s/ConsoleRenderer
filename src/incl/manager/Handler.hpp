#pragma once
#include "Renderer.hpp"
#include "../ext/consComm.hpp"
#include "../general.hpp"
#include <chrono>
#include <cstddef>
#include <memory>
#include <thread>
#include <mutex>
#include <vector>
#include "../objects/DefaultObj.hpp"

class Handler {
private:
  Renderer renderer;
  bool run{false};
  void physicsRun();
  void RenderRunner();
  std::mutex renderMutex{};
  bool isInDespawnRange(const std::shared_ptr<DefaultObj> &obj);

  // Debug and FPS variables for rendering.
  double renderCurrentFPS{0.0};
  double renderMaxFPS{0.0};
  double renderMinFPS{1e9};
  unsigned int totalObjectsCreated{0};

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

  template <typename T>
  std::shared_ptr<T> AddObject(T &&obj) {
    auto ptr = std::make_shared<std::decay_t<T>>(std::forward<T>(obj));
    {
      // Optionally lock if you add objects from multiple threads.
      std::lock_guard<std::mutex> lg(renderMutex);
      objpointer.push_back(ptr);
      totalObjectsCreated++;
    }
    return ptr;
  }
  template <typename T, typename... Args>
  std::shared_ptr<T> AddObjectConstruct(Args &&...args) {
    static_assert(std::is_base_of_v<DefaultObj, T>, "T must derive from DefaultObj");
    auto ptr = std::make_shared<T>(std::forward<Args>(args)...);
    {
      std::lock_guard<std::mutex> lg(renderMutex);
      objpointer.push_back(ptr);
      totalObjectsCreated++;
    }
    return ptr;
  }

  void RemoveObject(size_t ID);
  std::shared_ptr<DefaultObj> GetObject(size_t ID);
  void Render(bool state = true) { run = state; }
};

/*# pragma once
#include "Renderer.hpp"
#include "../ext/consComm.hpp"
#include "../general.hpp"
#include <chrono>
#include <cstddef>
#include <memory>
#include <thread>
#include <mutex>
#include <vector>
#include "../objects/DefaultObj.hpp"

class Handler {
private:
  Renderer renderer;
  bool run{false};
  void physicsRun();
  void RenderRunner();
  std::mutex renderMutex{};

  // Check if an object is outside the renderable range.
  bool isInDespawnRange(const std::shared_ptr<DefaultObj> &obj);

public:
  // Our container now holds polymorphic DefaultObj objects.
  std::vector<std::shared_ptr<DefaultObj>> objpointer{};
  float deltaT{0};
  unsigned int targetFrameRate{180};
  unsigned int ticks{100};
  unsigned int subticks{5};

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

  template <typename T>
  std::shared_ptr<T> AddObject(T &&obj) { // Deduce T from the provided object and decay it.
    auto ptr = std::make_shared<std::decay_t<T>>(std::forward<T>(obj));
    objpointer.push_back(ptr);
    return ptr;
  }
  template <typename T, typename... Args>
  std::shared_ptr<T> AddObjectConstruct(Args &&...args) {
    static_assert(std::is_base_of_v<DefaultObj, T>, "T must derive from DefaultObj");
    auto ptr = std::make_shared<T>(std::forward<Args>(args)...);
    objpointer.push_back(ptr);
    return ptr;
  }

  void RemoveObject(size_t ID);
  std::shared_ptr<DefaultObj> GetObject(size_t ID);
  void Render(bool state = true) { run = state; }
}; */