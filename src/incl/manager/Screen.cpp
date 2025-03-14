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
    framebuffer[i].AddToPrintBuf(printbuf);
    if (((i + 1) % m_width) == 0) printbuf << dcon::cmds::text::Reset << '\n';
  }
}
ScreenCell &Screen::get(unsigned int X, unsigned int Y) {
  if ((X >= m_width) || (Y >= m_height)) throw "tried to access screenBuffer out of range";
  else return framebuffer[X + m_width * Y];
}