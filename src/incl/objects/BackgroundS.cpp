#include "BackgroundS.hpp"
#include "../types/cell/ScreenCell.hpp"
#include "../general.hpp"

// void backG::onFrame(float deltaT) {}

// void backG::howDraw(Screen &screen) {

//   for (unsigned int x{(unsigned int)Start.x}; x < (unsigned int)End.x || x < screen.m_width; ++x)
//     for (unsigned int y{(unsigned int)Start.y}; y < (unsigned int)End.y || y < screen.m_height; ++y) {
//       auto &a{screen.get(x, y)};
//       if (a.bgColorZ < Z) a.setbgColor(Color, Z);
//     }
// }

#include <algorithm> // For std::min and std::max

void backgroundS::onFrame([[maybe_unused]] float deltaT) {} // No per-frame updates for a static background.

void backgroundS::howDraw(Screen &screen) { // Compute effective coordinates relative to the object's origin.
  Point3D effectiveStart = Origin + Start;
  Point3D effectiveEnd = Origin + End;

  // Determine the top - left and bottom - right corners of the region.
  float left = std::min(effectiveStart.x, effectiveEnd.x);
  float top = std::min(effectiveStart.y, effectiveEnd.y);
  float right = std::max(effectiveStart.x, effectiveEnd.x);
  float bottom = std::max(effectiveStart.y, effectiveEnd.y);

  // Clamp coordinates to the
  //     screen's dimensions. // Assuming screen coordinates start at 0.
  unsigned int x0 = static_cast<unsigned int>(std::max(0.0f, left));
  unsigned int y0 = static_cast<unsigned int>(std::max(0.0f, top));
  unsigned int x1 = static_cast<unsigned int>(std::min(right, static_cast<float>(screen.m_width)));
  unsigned int y1 = static_cast<unsigned int>(std::min(bottom, static_cast<float>(screen.m_height)));
  // Iterate over the region and set the
  //     cell's background color if its z-index is lower.
  for (unsigned int x = x0; x < x1; ++x) {
    for (unsigned int y = y0; y < y1; ++y) {
      auto &cell = screen.get(x, y);
      if (cell.bgColorZ < Origin.z) cell.setbgColor(Color, Origin.z);
    }
  }
}