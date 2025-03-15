#include "Handler.hpp"
#include "Renderer.hpp"
#include "../ext/Timer.hpp"
#include "Screen.hpp"
#include "../ext/consComm.hpp"
#include <iostream>

void Handler::RemoveObject(size_t ID) {
  std::lock_guard<std::recursive_mutex> lg{renderMutex};
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

// **New: Flush pending objects into objpointer**
void Handler::ProcessPendingObjects() {
  std::lock_guard<std::recursive_mutex> lg(renderMutex);
  while (!pendingObjects.empty()) {
    objpointer.push_back(pendingObjects.front());
    pendingObjects.pop();
  }
}

void Handler::physicsRun() {
  Timer timer{};
  double accumulator = 0.0;
  const double dt_tick = 1.0 / ticks;
  const double dt_sub = dt_tick / subticks;

  while (true) {
    if (run) {
      double frameTime = timer.lap();
      accumulator += frameTime;

      while (accumulator >= dt_tick) {
        for (unsigned int s = 0; s < subticks; ++s) {
          std::lock_guard<std::recursive_mutex> lg{renderMutex};

          ProcessPendingObjects(); // **New: Process pending additions before iterating**

          for (auto it = objpointer.begin(); it != objpointer.end();) {
            if (*it && ((*it)->isExpired() || isInDespawnRange(*it))) {
              it = objpointer.erase(it);
            } else {
              if (*it) (*it)->onFrame(static_cast<float>(dt_sub));
              ++it;
            }
          }
        }
        accumulator -= dt_tick;
      }

      if (frameTime < dt_tick) {
        auto sleepDuration =
            std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::duration<double>(dt_tick - frameTime));
        std::this_thread::sleep_for(sleepDuration);
      }
    } else {
      std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
  }
}

void Handler::RenderRunner() {
  Timer frameTimer{};
  Timer fpsTimer{};
  int frameCount = 0;

  while (true) {
    if (run) {
      static const double targetFrameDuration = 1.0 / targetFrameRate;

      renderer.DrawScreen();
      frameCount++;

      double elapsedFps = fpsTimer.elapsed();
      if (elapsedFps >= 1.0) {
        renderCurrentFPS = frameCount / elapsedFps;
        if (renderCurrentFPS > renderMaxFPS) renderMaxFPS = renderCurrentFPS;
        if (renderCurrentFPS < renderMinFPS) renderMinFPS = renderCurrentFPS;
        frameCount = 0;
        fpsTimer.reset();
      }

#ifdef d_DEBUG
      std::cout << dcon::cmds::screen::ClearLine << "Fps: " << std::setw(3) << (int)renderCurrentFPS << '/'
                << std::setw(3) << targetFrameRate << "\tmax: " << (int)renderMaxFPS << "  min: " << std::setw(3)
                << (int)renderMinFPS << '\n';
      std::cout << dcon::cmds::screen::ClearLine << "Obj: " << std::setw(4) << objpointer.size()
                << "\tTot. obj: " << totalObjectsCreated;
#endif

      double renderTime = frameTimer.lap();
      if (renderTime < targetFrameDuration) {
        auto sleepDuration = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::duration<double>(targetFrameDuration - renderTime));
        std::this_thread::sleep_for(sleepDuration);
      }
    } else {
      std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
  }
}
