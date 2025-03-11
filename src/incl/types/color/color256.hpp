#pragma once
#include "col.hpp"

struct Color256 {
  Col R, G, B;

  Color256(int r = 0, int g = 0, int b = 0) : R(r), G(g), B(b) {}
  Color256(const Col &r, const Col &g, const Col &b) : R(r), G(g), B(b) {}

  // Arithmetic with another color
  Color256 operator+(const Color256 &other) const { return Color256(R + other.R, G + other.G, B + other.B); }
  Color256 operator-(const Color256 &other) const { return Color256(R - other.R, G - other.G, B - other.B); }
  Color256 operator*(const Color256 &other) const { return Color256(R * other.R, G * other.G, B * other.B); }
  Color256 operator/(const Color256 &other) const { return Color256(R / other.R, G / other.G, B / other.B); }

  // Arithmetic with int
  Color256 operator+(int v) const { return Color256(R + v, G + v, B + v); }
  Color256 operator-(int v) const { return Color256(R - v, G - v, B - v); }
  Color256 operator*(int v) const { return Color256(R * v, G * v, B * v); }
  Color256 operator/(int v) const { return Color256(R / v, G / v, B / v); }

  // Compound assignment
  Color256 &operator+=(const Color256 &other) {
    R += other.R;
    G += other.G;
    B += other.B;
    return *this;
  }
  Color256 &operator-=(const Color256 &other) {
    R -= other.R;
    G -= other.G;
    B -= other.B;
    return *this;
  }
  Color256 &operator*=(const Color256 &other) {
    R *= other.R;
    G *= other.G;
    B *= other.B;
    return *this;
  }
  Color256 &operator/=(const Color256 &other) {
    R /= other.R;
    G /= other.G;
    B /= other.B;
    return *this;
  }

  Color256 &operator+=(int v) {
    R += v;
    G += v;
    B += v;
    return *this;
  }
  Color256 &operator-=(int v) {
    R -= v;
    G -= v;
    B -= v;
    return *this;
  }
  Color256 &operator*=(int v) {
    R *= v;
    G *= v;
    B *= v;
    return *this;
  }
  Color256 &operator/=(int v) {
    R /= v;
    G /= v;
    B /= v;
    return *this;
  }

  bool operator==(const Color256 &other) const { return R == other.R && G == other.G && B == other.B; }
  bool operator!=(const Color256 &other) const { return !(*this == other); }

  // Blend with another color using alpha (0.0 - 1.0)
  Color256 &blend(const Color256 &other, float alpha = 0.5f) {
    R.blend(other.R, alpha);
    G.blend(other.G, alpha);
    B.blend(other.B, alpha);
    return *this;
  }
};