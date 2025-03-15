#pragma once

#include "DefaultObj.hpp"
#include "../types/color/color256.hpp"
#include <cstdint>
#include <limits>
#include <string_view>

class text : public DefaultObj {
public:
  enum alignment : uint8_t {
    center = 0,
    left,
    right,
  };
  uint8_t align;
  std::string content;
  Color256 BackgroundCol;
  float lifetime, bgColorZ; // in seconds

  text(const std::string_view Text = "", const alignment Alignment = center, const Point3D &origin = {},
       const Point3D &velocity = {}, const Color256 &color = {255, 255, 255, 255},
       const Color256 &bgColor = {0, 0, 0, 255}, float BgColorZ = -99879, float despawnRad = 0,
       float Lifetime = std::numeric_limits<float>::max()) :
      DefaultObj(origin, velocity, color, despawnRad), align{Alignment}, content{Text}, BackgroundCol{bgColor},
      lifetime{Lifetime}, bgColorZ{BgColorZ == -99879 ? origin.z : BgColorZ} {}

  void onFrame(float deltaT) override;
  void howDraw(Screen &screen) override;
  bool isExpired() const override;
};
