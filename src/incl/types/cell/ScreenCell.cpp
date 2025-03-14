#include "ScreenCell.hpp"
#include "../../ext/consComm.hpp"

void ScreenCell::AddToPrintBuf(std::stringstream &s) {
  if (bgColorZ > colorZ) s << dcon::cmds::text::bg::setRGB(bgColor.R, bgColor.G, bgColor.G) << ' ';
  else {
    s << dcon::cmds::text::bg::setRGB(bgColor.R, bgColor.G, bgColor.G)
      << dcon::cmds::text::fo::setRGB(color.R, color.G, color.G) << repres.getChar();
  }
}