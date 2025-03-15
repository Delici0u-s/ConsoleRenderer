#pragma once

#include <memory>
#include <concepts>
#include "../types/Point3D.hpp"
#include "../types/color/color256.hpp"
#include "../manager/Screen.hpp"

// Define a Drawable concept that requires the needed methods and members.
template <typename T>
concept Drawable = requires(T t, Screen &screen, float deltaT) {
  { t.onFrame(deltaT) } -> std::same_as<void>;
  { t.howDraw(screen) } -> std::same_as<void>;
  { t.Origin } -> std::convertible_to<Point3D>;
  { t.DespawnRad } -> std::convertible_to<float>;
  { t.ID } -> std::convertible_to<size_t>;
};

class basicObj {
  // The type-erased interface
  struct Interface {
    virtual ~Interface() = default;
    virtual void onFrame(float deltaT) = 0;
    virtual void howDraw(Screen &screen) = 0;
    virtual const Point3D &getOrigin() const = 0;
    virtual float getDespawnRad() const = 0;
    virtual size_t getID() const = 0;
  };

  // The templated model storing a concrete Drawable type
  template <Drawable T>
  struct model : Interface {
    T object;
    model(T obj) : object(std::move(obj)) {}
    void onFrame(float deltaT) override { object.onFrame(deltaT); }
    void howDraw(Screen &screen) override { object.howDraw(screen); }
    const Point3D &getOrigin() const override { return object.Origin; }
    float getDespawnRad() const override { return object.DespawnRad; }
    size_t getID() const override { return object.ID; }
  };

  std::unique_ptr<Interface> ptr;

public:
  // Construct from any Drawable type
  template <Drawable T>
  basicObj(T obj) : ptr(std::make_unique<model<T>>(std::move(obj))) {}

  // Enable move semantics only (no copy)
  basicObj(basicObj &&) = default;
  basicObj &operator=(basicObj &&) = default;
  basicObj(const basicObj &) = delete;
  basicObj &operator=(const basicObj &) = delete;

  // Forwarded methods
  void onFrame(float deltaT) { ptr->onFrame(deltaT); }
  void howDraw(Screen &screen) { ptr->howDraw(screen); }
  const Point3D &getOrigin() const { return ptr->getOrigin(); }
  float getDespawnRad() const { return ptr->getDespawnRad(); }
  size_t getID() const { return ptr->getID(); }
};
