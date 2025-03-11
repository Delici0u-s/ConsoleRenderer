#ifndef DCON_CMDS_HPP
#define DCON_CMDS_HPP

#include <iostream> // For convenience functions that write directly to std::cout
#include <string>

namespace dcon {
namespace cmds {

// ----------------------------
// Cursor movement and manipulation
// ----------------------------
namespace cursor {
// Fixed sequences
constexpr const char *Up = "\033[F"; // Move cursor up one line (to beginning)
constexpr const char *Down =
    "\033[E"; // Move cursor down one line (to beginning)
constexpr const char *Forward =
    "\033[C"; // Move cursor forward (right) one column
constexpr const char *Backward =
    "\033[D"; // Move cursor backward (left) one column
constexpr const char *ResetPosition =
    "\033[H";                             // Reset cursor to top-left of screen
constexpr const char *Save = "\033[s";    // Save the current cursor position
constexpr const char *Restore = "\033[u"; // Restore the last saved position
constexpr const char *Hide = "\033[?25l"; // Hide the cursor
constexpr const char *Show = "\033[?25h"; // Show the cursor

// Parameterized functions

// Move to a specific row and column.
inline std::string moveTo(int row, int col) {
  return "\033[" + std::to_string(row) + ";" + std::to_string(col) + "H";
}

// Move relative: n is the number of positions, direction is one of:
// 'A' = up, 'B' = down, 'C' = forward/right, 'D' = backward/left.
inline std::string moveRelative(int n, char direction) {
  return "\033[" + std::to_string(n) + direction;
}

// Remove (delete) n lines above the cursor.
inline std::string removeLines(int n) {
  return "\033[" + std::to_string(n) + "M";
}

// Move the cursor to column n on the current row.
inline std::string moveToColumn(int n) {
  return "\033[" + std::to_string(n) + "G";
}
} // namespace cursor

// ----------------------------
// Screen clearing and scrolling
// ----------------------------
namespace screen {
// Fixed sequences
constexpr const char *ClearLine = "\033[2K"; // Clear the entire line
constexpr const char *ClearLineToEnd =
    "\033[K"; // Clear from cursor to end of line
constexpr const char *ClearLineToStart =
    "\033[1K"; // Clear from cursor to beginning of line
constexpr const char *Clear = "\033[2J";     // Clear the entire screen
constexpr const char *ClearToEnd = "\033[J"; // Clear screen from cursor to end
constexpr const char *ClearToStart =
    "\033[1J"; // Clear screen from cursor to beginning
constexpr const char *ClearDisplay =
    "\033[3J"; // Clear entire display including scrollback

// Parameterized functions

// Erase n characters starting at the cursor.
inline std::string eraseCharacters(int n) {
  return "\033[" + std::to_string(n) + "X";
}

// Scroll the display up by n lines.
inline std::string scrollUp(int n) { return "\033[" + std::to_string(n) + "S"; }

// Scroll the display down by n lines.
inline std::string scrollDown(int n) {
  return "\033[" + std::to_string(n) + "T";
}

// Insert n blank lines at the cursor position.
inline std::string insertLines(int n) {
  return "\033[" + std::to_string(n) + "L";
}
} // namespace screen

// ----------------------------
// Text styling and coloring
// ----------------------------
namespace text {
// Reset all text attributes.
constexpr const char *Reset = "\033[0m";

// Effects (ef)
namespace ef {

constexpr const char *Bold = "\033[1m";
constexpr const char *Dim = "\033[2m";
constexpr const char *Italic = "\033[3m";
constexpr const char *Underline = "\033[4m";
constexpr const char *Blink = "\033[5m";
constexpr const char *Inverse = "\033[7m";
constexpr const char *Hidden = "\033[8m";
constexpr const char *Strikethrough = "\033[9m";

// Reset Effects
constexpr const char *ResetBold = "\033[22m";
constexpr const char *ResetDim = "\033[22m"; // Same as ResetBold
constexpr const char *ResetItalic = "\033[23m";
constexpr const char *ResetUnderline = "\033[24m";
constexpr const char *ResetBlink = "\033[25m";
constexpr const char *ResetInverse = "\033[27m";
constexpr const char *ResetHidden = "\033[28m";
constexpr const char *ResetStrikethrough = "\033[29m";

} // namespace ef

// Foreground text colors.
namespace fo {
constexpr const char *Reset = "\033[39m";

constexpr const char *Black = "\033[30m";
constexpr const char *Red = "\033[31m";
constexpr const char *Green = "\033[32m";
constexpr const char *Yellow = "\033[33m";
constexpr const char *Blue = "\033[34m";
constexpr const char *Magenta = "\033[35m";
constexpr const char *Cyan = "\033[36m";
constexpr const char *White = "\033[37m";
constexpr const char *BrightBlack = "\033[90m";
constexpr const char *BrightRed = "\033[91m";
constexpr const char *BrightGreen = "\033[92m";
constexpr const char *BrightYellow = "\033[93m";
constexpr const char *BrightBlue = "\033[94m";
constexpr const char *BrightMagenta = "\033[95m";
constexpr const char *BrightCyan = "\033[96m";
constexpr const char *BrightWhite = "\033[97m";

// 256-color support (pass a value from 0 to 255)
inline std::string set256(int color) {
  return "\033[38;5;" + std::to_string(color) + "m";
}

// RGB support.
inline std::string setRGB(int r, int g, int b) {
  return "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" +
         std::to_string(b) + "m";
}
} // namespace fo

// Background colors.
namespace bg {
constexpr const char *Reset = "\033[49m";

constexpr const char *Black = "\033[40m";
constexpr const char *Red = "\033[41m";
constexpr const char *Green = "\033[42m";
constexpr const char *Yellow = "\033[43m";
constexpr const char *Blue = "\033[44m";
constexpr const char *Magenta = "\033[45m";
constexpr const char *Cyan = "\033[46m";
constexpr const char *White = "\033[47m";
constexpr const char *BrightBlack = "\033[100m";
constexpr const char *BrightRed = "\033[101m";
constexpr const char *BrightGreen = "\033[102m";
constexpr const char *BrightYellow = "\033[103m";
constexpr const char *BrightBlue = "\033[104m";
constexpr const char *BrightMagenta = "\033[105m";
constexpr const char *BrightCyan = "\033[106m";
constexpr const char *BrightWhite = "\033[107m";

// 256-color support.
inline std::string set256(int color) {
  return "\033[48;5;" + std::to_string(color) + "m";
}

// RGB support.
inline std::string setRGB(int r, int g, int b) {
  return "\033[48;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" +
         std::to_string(b) + "m";
}
} // namespace bg
} // namespace text

// ----------------------------
// Terminal modes and window title
// ----------------------------
namespace terminal {
// Enable/disable alternate screen buffer.
constexpr const char *AltScreen = "\033[?1049h";
constexpr const char *ExitAltScreen = "\033[?1049l";

// Enable/disable line wrapping.
constexpr const char *EnableWrap = "\033[?7h";
constexpr const char *DisableWrap = "\033[?7l";

// Set the terminal window title.
inline std::string setWindowTitle(const std::string &title) {
  return "\033]2;" + title + "\007";
}
} // namespace terminal

// ----------------------------
// Alerts and control characters
// ----------------------------
namespace alert {
// Audible bell.
constexpr const char *Bell = "\007";
} // namespace alert

namespace control {
// Common control characters.
constexpr const char *Tab = "\t";
constexpr const char *Backspace = "\b";
constexpr const char *CarriageReturn = "\r";
constexpr const char *NewLine = "\n";
constexpr const char *FormFeed = "\f";
constexpr const char *VerticalTab = "\v";
constexpr const char *Null = "\0";
constexpr const char *Escape = "\033";
} // namespace control

// ----------------------------
// Convenience utilities
// ----------------------------

// Reset the screen: clear entire screen and reset the cursor position.
inline void resetScreen() {
  std::cout << screen::Clear << cursor::ResetPosition;
}

// Compose a complete text style string from an effect, foreground, and optional
// background. Example: std::cout << textStyle(text::ef::Bold, text::fo::Red,
// text::bg::Black);
inline std::string textStyle(const std::string &effect,
                             const std::string &foreground,
                             const std::string &background = "") {
  return effect + foreground + background;
}

} // namespace cmds
} // namespace dcon

#endif // DCON_HPP
