#include "Screen.hpp"
#include "..//ext/consComm.hpp"
#include "src/incl/ext/consComm.hpp"
#include <cstddef>
#include <sstream>

void Screen::clear() {
  printbuf = {};
  printbuf << dcon::cmds::text::Reset << dcon::cmds::cursor::ResetPosition;
  for (auto &i : framebuffer)
    i.reset();
}

void Screen::WriteBuffer() {
  for (size_t i{0}; i < framebuffer.size(); ++i) {
    auto &V{framebuffer[i]};
    printbuf << dcon::cmds::text::fo::setRGB(V.color.R, V.color.G, V.color.G)
             << dcon::cmds::text::bg::setRGB(V.bgColor.R, V.bgColor.G, V.bgColor.G) << V.getChar();
    if (((i + 1) % m_width) == 0) printbuf << dcon::cmds::text::Reset << '\n';
  }
}
ScreenCell &Screen::get(unsigned int X, unsigned int Y) {
  if ((X >= m_width) || (Y >= m_height)) throw "tried to access screenBuffer out of range";
  else return framebuffer[X + m_width * Y];
}