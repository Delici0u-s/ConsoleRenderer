#pragma once
#include <cassert>

//-----------------------------------------------------------------------------
// Approximate factorial at compile time (used for the series expansion).
//-----------------------------------------------------------------------------
constexpr float factorial(int n) { return (n <= 1) ? 1.0f : (n * factorial(n - 1)); }

//-----------------------------------------------------------------------------
// Approximate e^x at compile time using a truncated power series:
//   e^x = 1 + x + x^2 / 2! + x^3 / 3! + ... (up to `terms`).
//-----------------------------------------------------------------------------
constexpr float constexpr_exp(float x, int terms = 10) {
  float sum = 1.0f;  // n=0 => x^0 / 0! = 1
  float term = 1.0f; // Current term in the series
  for (int i = 1; i < terms; ++i) {
    term *= x / static_cast<float>(i); // x^i / i!
    sum += term;
  }
  return sum;
}

//-----------------------------------------------------------------------------
// Approximate square root at compile time using Newton-Raphson.
//-----------------------------------------------------------------------------
constexpr float constexpr_sqrt(float x, int iterations = 10) {
  if (x <= 0.0f) return 0.0f;
  float guess = x;
  for (int i = 0; i < iterations; ++i) {
    guess = 0.5f * (guess + x / guess);
  }
  return guess;
}

struct Point3D {
  float x, y, z;

  //-------------------------------------------------------------------------
  // Constructors
  //-------------------------------------------------------------------------
  constexpr Point3D(float X = 0, float Y = 0, float Z = 0) : x(X), y(Y), z(Z) {}
  constexpr Point3D(const Point3D &other) = default;
  constexpr Point3D &operator=(const Point3D &other) = default;

  //-------------------------------------------------------------------------
  // Comparison
  //-------------------------------------------------------------------------
  constexpr bool operator==(const Point3D &other) const { return (x == other.x && y == other.y && z == other.z); }
  constexpr bool operator!=(const Point3D &other) const { return !(*this == other); }

  //-------------------------------------------------------------------------
  // Arithmetic operators with Point3D
  //-------------------------------------------------------------------------
  constexpr Point3D operator+(const Point3D &other) const { return Point3D(x + other.x, y + other.y, z + other.z); }
  constexpr Point3D operator-(const Point3D &other) const { return Point3D(x - other.x, y - other.y, z - other.z); }
  constexpr Point3D operator*(float scalar) const { return Point3D(x * scalar, y * scalar, z * scalar); }
  constexpr Point3D operator/(float scalar) const { return Point3D(x / scalar, y / scalar, z / scalar); }

  //-------------------------------------------------------------------------
  // Compound assignment operators
  //-------------------------------------------------------------------------
  constexpr Point3D &operator+=(const Point3D &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
  }
  constexpr Point3D &operator-=(const Point3D &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
  }
  constexpr Point3D &operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
  }
  constexpr Point3D &operator/=(float scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
  }

  //-------------------------------------------------------------------------
  // Arithmetic operators with a single scalar
  //-------------------------------------------------------------------------
  constexpr Point3D operator+(float value) const { return Point3D(x + value, y + value, z + value); }
  constexpr Point3D operator-(float value) const { return Point3D(x - value, y - value, z - value); }
  constexpr Point3D &operator+=(float value) {
    x += value;
    y += value;
    z += value;
    return *this;
  }
  constexpr Point3D &operator-=(float value) {
    x -= value;
    y -= value;
    z -= value;
    return *this;
  }

  //-------------------------------------------------------------------------
  // Unary negation
  //-------------------------------------------------------------------------
  constexpr Point3D operator-() const { return Point3D(-x, -y, -z); }

  //-------------------------------------------------------------------------
  // Indexing operators (with bounds checking)
  //-------------------------------------------------------------------------
  constexpr float operator[](int index) const {
    assert(index >= 0 && index < 3 && "Index out of bounds");
    return (index == 0 ? x : (index == 1 ? y : z));
  }
  float &operator[](int index) {
    assert(index >= 0 && index < 3 && "Index out of bounds");
    return (index == 0 ? x : (index == 1 ? y : z));
  }

  //-------------------------------------------------------------------------
  // Data pointer access
  //-------------------------------------------------------------------------
  constexpr const float *data() const { return &x; }
  float *data() { return &x; }

  //-------------------------------------------------------------------------
  // Magnitude (length) and squaredMagnitude
  //-------------------------------------------------------------------------
  constexpr float magnitude() const { return constexpr_sqrt(x * x + y * y + z * z); }
  constexpr float squaredMagnitude() const { return (x * x + y * y + z * z); }

  //-------------------------------------------------------------------------
  // Distance to another point
  //-------------------------------------------------------------------------
  constexpr float distanceTo(const Point3D &other) const {
    float dx = x - other.x;
    float dy = y - other.y;
    float dz = z - other.z;
    return constexpr_sqrt(dx * dx + dy * dy + dz * dz);
  }

  //-------------------------------------------------------------------------
  // Normalize (returns a unit vector in the same direction)
  //-------------------------------------------------------------------------
  constexpr Point3D normalized() const {
    float mag = magnitude();
    return (mag == 0.0f) ? Point3D(0.0f, 0.0f, 0.0f) : (*this / mag);
  }

  //-------------------------------------------------------------------------
  // Dot product
  //-------------------------------------------------------------------------
  constexpr float dot(const Point3D &other) const { return (x * other.x + y * other.y + z * other.z); }

  //-------------------------------------------------------------------------
  // Cross product
  //-------------------------------------------------------------------------
  constexpr Point3D cross(const Point3D &other) const {
    return Point3D(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
  }

  //-------------------------------------------------------------------------
  // LINEAR LERP
  //   Static version: Point3D::linearLerp(a, b, t)
  //   Member version: a.linearLerp(b, t)
  //-------------------------------------------------------------------------
  constexpr static Point3D linearLerp(const Point3D &a, const Point3D &b, float t) { return a * (1.0f - t) + b * t; }
  constexpr Point3D linearLerp(const Point3D &target, float t) const {
    // 'this' is the "a" in the equation
    return (*this) * (1.0f - t) + target * t;
  }
  constexpr Point3D &linearLerpAssign(const Point3D &target, float t) {
    *this = (*this) * (1.0f - t) + target * t;
    return *this;
  }

  //-------------------------------------------------------------------------
  // EXPONENTIAL DECAY
  //   Static version: Point3D::expDecay(a, b, decay, dt)
  //   Member version: a.expDecay(b, decay, dt)
  //
  //   Moves 'a' toward 'b' by factor e^(-decay * dt).
  //-------------------------------------------------------------------------
  constexpr static Point3D expDecay(const Point3D &a, const Point3D &b, float decay, float dt, int expTerms = 10) {
    return b + (a - b) * constexpr_exp(-decay * dt, expTerms);
  }
  constexpr Point3D expDecay(const Point3D &target, float decay, float dt, int expTerms = 10) const {
    // 'this' is the "a" in the equation
    return target + ((*this) - target) * constexpr_exp(-decay * dt, expTerms);
  }
  constexpr Point3D &expDecayAssign(const Point3D &target, float decay, float dt, int expTerms = 10) {
    *this = target + ((*this) - target) * constexpr_exp(-decay * dt, expTerms);
    return *this;
  }

  //-------------------------------------------------------------------------
  // Return the origin (0,0,0)
  //-------------------------------------------------------------------------
  constexpr static Point3D origin() { return Point3D(0.0f, 0.0f, 0.0f); }

  //-------------------------------------------------------------------------
  // Setter
  //-------------------------------------------------------------------------
  constexpr void set(float newX, float newY, float newZ) {
    x = newX;
    y = newY;
    z = newZ;
  }
  constexpr void set(Point3D &p) { (*this) = p; }
};

//-----------------------------------------------------------------------------
// Scalar multiplication from the left-hand side
//-----------------------------------------------------------------------------
constexpr Point3D operator*(float scalar, const Point3D &p) { return p * scalar; }
