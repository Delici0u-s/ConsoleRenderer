#pragma once
#include <cmath>

// constexpr square root approximation using Newton-Raphson (for C++20)
constexpr float constexpr_sqrt(float x, int iterations = 10) {
  if (x <= 0.0f) return 0.0f;
  float guess = x;
  for (int i = 0; i < iterations; ++i)
    guess = 0.5f * (guess + x / guess);
  return guess;
}

struct Point2D {
  float x = 0.0f;
  float y = 0.0f;

  // Default constructor
  constexpr Point2D() = default;

  // Parameterized constructor
  constexpr Point2D(float X, float Y) : x(X), y(Y) {}

  // Copy constructor
  constexpr Point2D(const Point2D &other) = default;

  // Assignment operator
  constexpr Point2D &operator=(const Point2D &other) = default;

  // Equality operators
  constexpr bool operator==(const Point2D &other) const { return x == other.x && y == other.y; }

  constexpr bool operator!=(const Point2D &other) const { return !(*this == other); }

  // Arithmetic operators
  constexpr Point2D operator+(const Point2D &other) const { return Point2D(x + other.x, y + other.y); }

  constexpr Point2D operator-(const Point2D &other) const { return Point2D(x - other.x, y - other.y); }

  constexpr Point2D operator*(float scalar) const { return Point2D(x * scalar, y * scalar); }

  constexpr Point2D operator/(float scalar) const { return Point2D(x / scalar, y / scalar); }

  // Compound assignment operators
  constexpr Point2D &operator+=(const Point2D &other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  constexpr Point2D &operator-=(const Point2D &other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  constexpr Point2D &operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
  }

  constexpr Point2D &operator/=(float scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
  }

  // Magnitude (length) of the vector
  constexpr float magnitude() const { return constexpr_sqrt(x * x + y * y); }

  // Distance to another point
  constexpr float distanceTo(const Point2D &other) const {
    float dx = x - other.x;
    float dy = y - other.y;
    return constexpr_sqrt(dx * dx + dy * dy);
  }

  // Normalize the vector (returns a unit vector in the same direction)
  constexpr Point2D normalized() const {
    float mag = magnitude();
    return (mag == 0.0f) ? Point2D(0.0f, 0.0f) : (*this / mag);
  }

  // Dot product
  constexpr float dot(const Point2D &other) const { return x * other.x + y * other.y; }
};

// Optional: Scalar multiplication from left-hand side
constexpr Point2D operator*(float scalar, const Point2D &p) { return p * scalar; }
