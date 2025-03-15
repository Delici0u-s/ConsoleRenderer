#pragma once
#include <algorithm>
#include <cstdint>
#include <stdexcept>

struct Color256 {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
  union {
    struct {
      unsigned char R;
      unsigned char G;
      unsigned char B;
      unsigned char A;
    };
    uint32_t RGBA;
  };
#pragma GCC diagnostic pop

  // Default constructor: black with full opacity
  Color256() : R(0), G(0), B(0), A(255) {}

  // Component-wise constructor
  Color256(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255) : R(r), G(g), B(b), A(a) {}

  // Grayscale constructor
  Color256(unsigned char gray, unsigned char a = 255) : R(gray), G(gray), B(gray), A(a) {}

  // Packed 32-bit RGBA value constructor
  Color256(uint32_t rgba) : RGBA(rgba) {}

  // Hex string constructor (e.g., "#RRGGBB" or "RRGGBB")
  Color256(const std::string &hex) {
    std::string hexClean = hex;
    if (!hex.empty() && hex[0] == '#') hexClean = hex.substr(1); // Remove leading '#'

    if (hexClean.length() != 6 && hexClean.length() != 8)
      throw std::invalid_argument("Color256 hex string must be 6 or 8 characters long");

    auto hexToByte = [](const std::string &str, size_t pos) -> unsigned char {
      return static_cast<unsigned char>(std::stoul(str.substr(pos, 2), nullptr, 16));
    };

    R = hexToByte(hexClean, 0);
    G = hexToByte(hexClean, 2);
    B = hexToByte(hexClean, 4);
    A = (hexClean.length() == 8) ? hexToByte(hexClean, 6) : 255;
  }

  // Copy constructor
  Color256(const Color256 &other) : RGBA(other.RGBA) {}

  // Copy assignment operator
  Color256 &operator=(const Color256 &other) {
    if (this != &other) { RGBA = other.RGBA; }
    return *this;
  }

  // Move constructor (trivial)
  Color256(Color256 &&other) noexcept : RGBA(other.RGBA) {}

  // Move assignment operator (trivial)
  Color256 &operator=(Color256 &&other) noexcept {
    if (this != &other) { RGBA = other.RGBA; }
    return *this;
  }

  // Blends another color 'over' this one using standard alpha compositing.
  // The 'alpha' parameter scales the source's effective alpha.
  Color256 &blend(const Color256 &other, float alpha = 1.0f) {
    float srcAlpha = (other.A / 255.0f) * alpha;
    float dstAlpha = A / 255.0f;
    float outAlpha = srcAlpha + dstAlpha * (1.0f - srcAlpha);

    if (outAlpha > 0.0f) {
      R = static_cast<unsigned char>((other.R * srcAlpha + R * dstAlpha * (1.0f - srcAlpha)) / outAlpha + 0.5f);
      G = static_cast<unsigned char>((other.G * srcAlpha + G * dstAlpha * (1.0f - srcAlpha)) / outAlpha + 0.5f);
      B = static_cast<unsigned char>((other.B * srcAlpha + B * dstAlpha * (1.0f - srcAlpha)) / outAlpha + 0.5f);
      A = static_cast<unsigned char>(outAlpha * 255.0f + 0.5f);
    }
    return *this;
  }

  // -------------------------
  // Comparison Operators
  // -------------------------
  bool operator==(const Color256 &other) const { return RGBA == other.RGBA; }

  bool operator!=(const Color256 &other) const { return !(*this == other); }

  // -------------------------
  // Arithmetic Operators
  // -------------------------
  // Helper function for clamping values to [0, 255]
  static unsigned char clamp(int value) { return static_cast<unsigned char>(std::min(255, std::max(0, value))); }

  // Component-wise addition (with saturation)
  Color256 operator+(const Color256 &other) const {
    return Color256(clamp(R + other.R), clamp(G + other.G), clamp(B + other.B), clamp(A + other.A));
  }

  // Component-wise subtraction (with floor at 0)
  Color256 operator-(const Color256 &other) const {
    return Color256(clamp(R - other.R), clamp(G - other.G), clamp(B - other.B), clamp(A - other.A));
  }

  // Multiply color by a scalar factor (applied to each component)
  Color256 operator*(float factor) const {
    return Color256(clamp(static_cast<int>(R * factor + 0.5f)), clamp(static_cast<int>(G * factor + 0.5f)),
                    clamp(static_cast<int>(B * factor + 0.5f)), clamp(static_cast<int>(A * factor + 0.5f)));
  }

  // Divide color by a scalar factor (applied to each component)
  Color256 operator/(float factor) const {
    if (factor == 0.0f) { throw std::runtime_error("Division by zero in Color256 operator/."); }
    float invFactor = 1.0f / factor;
    return *this * invFactor;
  }

  // -------------------------
  // Compound Assignment Operators
  // -------------------------
  Color256 &operator+=(const Color256 &other) {
    *this = *this + other;
    return *this;
  }

  Color256 &operator-=(const Color256 &other) {
    *this = *this - other;
    return *this;
  }

  Color256 &operator*=(float factor) {
    *this = *this * factor;
    return *this;
  }

  Color256 &operator/=(float factor) {
    *this = *this / factor;
    return *this;
  }
};
