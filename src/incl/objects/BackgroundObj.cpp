#include "BackgroundObj.hpp"
#include "../types/color/color256.hpp"
#include "../types/Point3D.hpp"
#include "src/incl/manager/Screen.hpp"

namespace obj {
void BackgoundS::onFrame([[maybe_unused]] const float deltaT) {}

void BackgoundS::howDraw(Screen &screen) {
  const unsigned int startX{(unsigned int)(End.x < Start.x ? End.x : Start.x)};
  const unsigned int startY{(unsigned int)(End.y < Start.y ? End.y : Start.y)};
  const unsigned int endX{(unsigned int)(End.x > Start.x ? End.x : Start.x)};
  const unsigned int endY{(unsigned int)(End.y > Start.y ? End.y : Start.y)};
  if (startX <= screen.m_width && startY <= screen.m_height) {
    for (unsigned int x{startX}; x < endX || x < screen.m_width; ++x)
      for (unsigned int y{startY}; y < endY || y < screen.m_height; ++x) {
        auto &a{screen.get(x, y)};
        if (a.bgColorZ < Z) a.setbgColor(Color, Z);
      }
  }
}
} // namespace obj