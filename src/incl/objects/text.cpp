#include "text.hpp"
#include "../types/cell/ScreenCell.hpp"
#include "../general.hpp"
#include <vector>
#include <string_view>

void text::onFrame([[maybe_unused]] float deltaT) { // Optionally update lifetime
  lifetime -= deltaT;
}

void text::howDraw(Screen &screen) { // Split the content by newline into individual lines.
  std::vector<std::string_view> lines;
  size_t start = 0;
  size_t pos = content.find('\n');
  while (pos != std::string::npos) {
    lines.push_back(std::string_view(content.data() + start, pos - start));
    start = pos + 1;
    pos = content.find('\n', start);
  }
  lines.push_back(std::string_view(content.data() + start, content.size() - start));

  // Determine the maximum line width (in characters) among all lines.
  unsigned int maxLineWidth = 0;
  for (auto line : lines) {
    if (line.size() > maxLineWidth) maxLineWidth = line.size();
  }

  // For each line, compute the starting X offset based on the alignment.
  for (unsigned int lineIndex = 0; lineIndex < lines.size(); ++lineIndex) {
    std::string_view line = lines[lineIndex];
    int offsetX = 0;
    switch (align) {
    case text::alignment::left: offsetX = 0; break;
    case text::alignment::center: offsetX = (maxLineWidth - line.size()) / 2; break;
    case text::alignment::right: offsetX = maxLineWidth - line.size(); break;
    default: offsetX = 0; break;
    }

    // For each character in the current line, update the corresponding cell.
    for (unsigned int charIndex = 0; charIndex < line.size(); ++charIndex) {
      unsigned int cellX = static_cast<unsigned int>(Origin.x) + offsetX + charIndex;
      unsigned int cellY = static_cast<unsigned int>(Origin.y) + lineIndex;
      try {
        auto &cell = screen.get(cellX, cellY);

        // if (BackgroundCol.A != 0 && cell.bgColorZ <= bgColorZ) cell.setbgColor(BackgroundCol, Origin.z);
        if ((bgColorZ != -99879)) cell.setbgColor(BackgroundCol, Origin.z);
        cell.setColor(Color, Origin.z);
        if (cell.repres.zpos <= Origin.z) cell.repres.setChar(std::string_view(&line[charIndex], 1), Origin.z);
      } catch (...) { ; }
    }
  }
}
bool text::isExpired() const { return lifetime <= 0; }