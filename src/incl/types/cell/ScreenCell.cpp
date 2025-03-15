#include "ScreenCell.hpp"
#include "../../ext/consComm.hpp"

void ScreenCell::AddToPrintBuf(std::stringstream &s) {
  if (bgColorZ > colorZ) s << dcon::cmds::text::bg::setRGB(bgColor.R, bgColor.G, bgColor.B) << ' ';
  else {
    s << dcon::cmds::text::bg::setRGB(bgColor.R, bgColor.G, bgColor.B)
      << dcon::cmds::text::fo::setRGB(color.R, color.G, color.B) << repres.getChar();
  }
}

void ScreenCell::setColor(const Color256 &newColor, float newZ) {
  // Only update if the new object is on top (or equal if you want to blend in
  // that case)
  if (newZ < this->colorZ) return;

  float alpha = newColor.A / 255.0f;
  if (alpha >= 1.0f) { // Fully opaque: override existing color completely.
    this->color = newColor;
  } else { // Blend newColor
    // with the current color.
    this->color.R = static_cast<uint8_t>(newColor.R * alpha + this->color.R * (1 - alpha));
    this->color.G = static_cast<uint8_t>(newColor.G * alpha + this->color.G * (1 - alpha));
    this->color.B = static_cast<uint8_t>(newColor.B * alpha + this->color.B * (1 - alpha)); // Optionally,
    // set alpha to 255 if the resulting composite is considered opaque.
    this->color.A = 255;
  } // Update the
  // z-index for the cell.
  this->colorZ = newZ;
}

void ScreenCell::setbgColor(const Color256 &newColor, float newZ) {
  if (newZ < this->bgColorZ) return;
  float alpha = newColor.A / 255.0f;
  if (alpha >= 1.0f) {
    this->bgColor = newColor;
  } else {
    this->bgColor.R = static_cast<uint8_t>(newColor.R * alpha + this->bgColor.R * (1 - alpha));
    this->bgColor.G = static_cast<uint8_t>(newColor.G * alpha + this->bgColor.G * (1 - alpha));
    this->bgColor.B = static_cast<uint8_t>(newColor.B * alpha + this->bgColor.B * (1 - alpha));
    this->bgColor.A = 255;
  }
  this->bgColorZ = newZ;
}