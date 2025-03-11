#include "Screen.hpp"
#include "..//ext/consComm.hpp"
#include <cstddef>
#include <sstream>

void Screen::clear() {
  printbuf.clear();
  printbuf << dcon::cmds::text::Reset << dcon::cmds::cursor::moveRelative(m_width, 'D')
           << dcon::cmds::cursor::moveRelative(m_height + 2, 'A');
  for (auto &i : framebuffer)
    i.left.reset(), i.right.reset();
}

inline void addtobuf(std::stringstream &b, CellFragment &V) {
  b << dcon::cmds::text::fo::setRGB(V.color.R.value, V.color.G.value, V.color.G.value)
    << dcon::cmds::text::bg::setRGB(V.bgColor.R.value, V.bgColor.G.value, V.bgColor.G.value) << V.getChar();
};

void Screen::WriteBuffer() {
  for (size_t i{0}; i < framebuffer.size(); ++i) {
    addtobuf(printbuf, framebuffer[i].left);
    addtobuf(printbuf, framebuffer[i].right);
    if (((i + 1) % m_width) == 0) printbuf << dcon::cmds::text::Reset << '\n';
  }
}
ScreenCell &Screen::get(unsigned int X, unsigned int Y) {
  if ((X >= 0 && X <= m_width) || (Y >= 0 && Y <= m_height)) return framebuffer[X + m_width * Y];
  else throw "tried to access screenBuffer out of range";
}