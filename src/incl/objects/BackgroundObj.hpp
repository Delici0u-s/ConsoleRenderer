#include "DefaultObj.hpp"
#include "../types/color/color256.hpp"
#include "../types/Point3D.hpp"
#include "src/incl/manager/Screen.hpp"

namespace obj {
struct BackgoundS : public DefaultObj {
  Point3D End, Start;
  float Z;
  BackgoundS(const Color256 &color, const Point3D &end = {0, 0}, const Point3D &start = {0, 0}, const float z = 1) :
      DefaultObj({}, {}, color), End{end}, Start{start}, Z{z} {}

  virtual void onFrame([[maybe_unused]] const float deltaT) override;

  virtual void howDraw(Screen &screen) override;
  // {
  //   const unsigned int startX{(unsigned int)(End.x < Start.x ? End.x : Start.x)};
  //   const unsigned int startY{(unsigned int)(End.y < Start.y ? End.y : Start.y)};
  //   const unsigned int endX{(unsigned int)(End.x > Start.x ? End.x : Start.x)};
  //   const unsigned int endY{(unsigned int)(End.y > Start.y ? End.y : Start.y)};
  //   if (startX <= screen.m_width && startY <= screen.m_height) {
  //     for (unsigned int x{startX}; x < endX || x < screen.m_width; ++x)
  //       for (unsigned int y{startY}; y < endY || y < screen.m_height; ++x) {
  //         auto &a{screen.get(x, y)};
  //         if (a.bgColorZ < Z) a.setbgColor(Color, Z);
  //       }
  //   }
  // }
};
} // namespace obj