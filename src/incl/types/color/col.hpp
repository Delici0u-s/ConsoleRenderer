#pragma once
#include <algorithm>

struct Col {
  int value;

  Col(int v) : value(std::clamp(v, 0, 255)) {}

  // Copy constructor
  Col(const Col &other) : value(other.value) {}

  // Assignment operator
  Col &operator=(int v) {
    value = std::clamp(v, 0, 255);
    return *this;
  }

  // Arithmetic operators with another Col
  Col operator+(const Col &other) const { return Col(value + other.value); }

  Col operator-(const Col &other) const { return Col(value - other.value); }

  Col operator*(const Col &other) const { return Col(value * other.value); }

  Col operator/(const Col &other) const { return Col(other.value != 0 ? value / other.value : 0); }

  // Arithmetic operators with int
  Col operator+(int v) const { return Col(value + v); }

  Col operator-(int v) const { return Col(value - v); }

  Col operator*(int v) const { return Col(value * v); }

  Col operator/(int v) const { return Col(v != 0 ? value / v : 0); }

  // Compound assignment operators with Col
  Col &operator+=(const Col &other) {
    value = std::clamp(value + other.value, 0, 255);
    return *this;
  }

  Col &operator-=(const Col &other) {
    value = std::clamp(value - other.value, 0, 255);
    return *this;
  }

  Col &operator*=(const Col &other) {
    value = std::clamp(value * other.value, 0, 255);
    return *this;
  }

  Col &operator/=(const Col &other) {
    value = std::clamp((other.value != 0 ? value / other.value : 0), 0, 255);
    return *this;
  }

  // Compound assignment operators with int
  Col &operator+=(int v) {
    value = std::clamp(value + v, 0, 255);
    return *this;
  }

  Col &operator-=(int v) {
    value = std::clamp(value - v, 0, 255);
    return *this;
  }

  Col &operator*=(int v) {
    value = std::clamp(value * v, 0, 255);
    return *this;
  }

  Col &operator/=(int v) {
    value = std::clamp((v != 0 ? value / v : 0), 0, 255);
    return *this;
  }

  // Comparison operators
  bool operator==(const Col &other) const { return value == other.value; }

  bool operator!=(const Col &other) const { return value != other.value; }

  bool operator<(const Col &other) const { return value < other.value; }

  bool operator<=(const Col &other) const { return value <= other.value; }

  bool operator>(const Col &other) const { return value > other.value; }

  bool operator>=(const Col &other) const { return value >= other.value; }

  // Blend with another Col using alpha (0.0 - 1.0)
  constexpr void blend(const Col &other, float alpha = 0.5f) {
    value = (value * (1 - alpha) + other.value * alpha + 0.5f);
  }
};
