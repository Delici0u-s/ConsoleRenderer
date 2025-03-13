#ifndef DCON_KEY_HPP
#define DCON_KEY_HPP

#include <vector>
#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h>
#else // assume Linux
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
#endif

namespace dcon {
namespace Key {

// The key enumeration supports all possible key inputs.
// Using an enum class ensures strong type-safety and scoped enumerators.
enum class key : int {
  BACKSPACE = 8,
  TAB = 9,
  NEWLINE = 10,
  ESCAPE = 27,

  SPACE = 32,
  EXCLAMATION = 33,
  DOUBLE_QUOTE = 34,
  HASH = 35,
  DOLLAR = 36,
  PERCENT = 37,
  AMPERSAND = 38,
  SINGLE_QUOTE = 39,
  OPEN_PAREN = 40,
  CLOSE_PAREN = 41,
  ASTERISK = 42,
  PLUS = 43,
  COMMA = 44,
  MINUS = 45,
  PERIOD = 46,
  SLASH = 47,
  ZERO = 48,
  ONE = 49,
  TWO = 50,
  THREE = 51,
  FOUR = 52,
  FIVE = 53,
  SIX = 54,
  SEVEN = 55,
  EIGHT = 56,
  NINE = 57,
  COLON = 58,
  SEMICOLON = 59,
  LESS_THAN = 60,
  EQUAL = 61,
  GREATER_THAN = 62,
  QUESTION = 63,
  AT = 64,
  A = 65,
  B = 66,
  C = 67,
  D = 68,
  E = 69,
  F = 70,
  G = 71,
  H = 72,
  I = 73,
  J = 74,
  K = 75,
  L = 76,
  M = 77,
  N = 78,
  O = 79,
  P = 80,
  Q = 81,
  R = 82,
  S = 83,
  T = 84,
  U = 85,
  V = 86,
  W = 87,
  X = 88,
  Y = 89,
  Z = 90,
  OPEN_BRACKET = 91,
  BACKSLASH = 92,
  CLOSE_BRACKET = 93,
  CARET = 94,
  UNDERSCORE = 95,
  BACKTICK = 96,
  a = 97,
  b = 98,
  c = 99,
  d = 100,
  e = 101,
  f = 102,
  g = 103,
  h = 104,
  i = 105,
  j = 106,
  k = 107,
  l = 108,
  m = 109,
  n = 110,
  o = 111,
  p = 112,
  q = 113,
  r = 114,
  s = 115,
  t = 116,
  u = 117,
  v = 118,
  w = 119,
  x = 120,
  y = 121,
  z = 122,
  OPEN_BRACE = 123,
  VERTICAL_BAR = 124,
  CLOSE_BRACE = 125,
  TILDE = 126,
  DELETE_KEY = 127,

  // Extended characters (from Linux mapping)
  A_UMLAUT = 132,         // ä
  U_UMLAUT = 129,         // ü
  O_UMLAUT = 148,         // ö
  CAPITAL_A_UMLAUT = 142, // Ä
  CAPITAL_O_UMLAUT = 153, // Ö
  CAPITAL_U_UMLAUT = 154, // Ü
  SZ = 225,               // ß
  MICRO = 230,            // µ
  SECTION = 245,          // §
  DEGREE = 248,           // °
  TWO_SUPER = 253,        // ²
  THREE_SUPER = 252,      // ³
  ACUTE = 239,            // ´

  // Special keys (non-printable, negative values)
  UP_ARROW = -38,
  DOWN_ARROW = -40,
  LEFT_ARROW = -37,
  RIGHT_ARROW = -39,
  PAGE_UP = -33,
  PAGE_DOWN = -34,
  HOME = -36,
  END = -35,
  INSERT = -45,
  NUM_LOCK = -144,
  CAPS_LOCK = -20,
  WINDOWS_KEY = -91,
  CONTEXT_MENU_KEY = -93,
  F1 = -112,
  F2 = -113,
  F3 = -114,
  F4 = -115,
  F5 = -116,
  F6 = -117,
  F7 = -118,
  F8 = -119,
  F9 = -120,
  F10 = -121,
  F11 = -122,
  F12 = -123
};

// Helper function to check for modifier key events.
// This filters out keys that represent shift, control, or alt keys (including left/right variants)
// as well as a few extra cases that should be ignored.
inline bool isModifierKey(int keyVal) {
  return (keyVal == -16 || keyVal == -17 || keyVal == -18 || keyVal == -160 || keyVal == -161 || keyVal == -162 ||
          keyVal == -163 || keyVal == -164 || keyVal == -165 || keyVal == -220 || keyVal == -221 || keyVal == -191 ||
          keyVal == -52 || keyVal == -53 || keyVal == -54 || keyVal == -12);
}

// A simple sleep function (in seconds)
inline void sleep(double t) {
  if (t > 0.0) {
#if defined(_WIN32)
    Sleep((DWORD)(t * 1000));
#elif defined(__linux__)
    struct timespec req = {0};
    req.tv_sec = (time_t)t;
    req.tv_nsec = (long)((t - req.tv_sec) * 1e9);
    nanosleep(&req, nullptr);
#endif
  }
}

#if defined(_WIN32)
// --------------------------------------------------------------------------
// Windows Implementation of "isKeyDown"
// Uses the efficient GetAsyncKeyState API to check if the key is currently down.
inline bool isKeyDown(key k) {
  int keyVal = static_cast<int>(k);
  // For special keys (stored as negative values) convert to the positive virtual key code.
  if (keyVal < 0) keyVal = -keyVal;
  return (GetAsyncKeyState(keyVal) & 0x8000) != 0;
}
#elif defined(__linux__)
// --------------------------------------------------------------------------
// Linux Implementation (Terminal Mode)
// Due to limitations with non-graphical terminals, real-time key state detection is not available.
// For a full implementation, consider integrating with X11, SDL, or ncurses.
inline bool isKeyDown(key /*k*/) { return false; }

// A RAII helper class to manage terminal mode changes for Linux.
// It switches to non-canonical mode without echo, and restores the original settings on destruction.
class TerminalSettings {
public:
  TerminalSettings() {
    tcgetattr(0, &old_term);
    term = old_term;
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &term);
  }
  ~TerminalSettings() { tcsetattr(0, TCSANOW, &old_term); }

private:
  struct termios old_term, term;
};
#endif

// --------------------------------------------------------------------------
// asyncGetCharV
// Polls for key events and returns them in a vector.
// (On Windows, only key-down events are processed; on Linux, terminal input is polled.)
inline std::vector<key> asyncGetCharV() {
  std::vector<key> keys;
#if defined(_WIN32)
  HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
  if (hInput == INVALID_HANDLE_VALUE) return keys;
  DWORD numEvents = 0;
  GetNumberOfConsoleInputEvents(hInput, &numEvents);
  if (numEvents == 0) return keys;
  std::vector<INPUT_RECORD> buffer(numEvents);
  DWORD eventsRead = 0;
  if (ReadConsoleInput(hInput, buffer.data(), numEvents, &eventsRead)) {
    for (DWORD i = 0; i < eventsRead; i++) {
      if (buffer[i].EventType == KEY_EVENT) {
        // Process both key-down and key-up events if needed.
        if (buffer[i].Event.KeyEvent.bKeyDown) {
          int ca = static_cast<int>(buffer[i].Event.KeyEvent.uChar.AsciiChar);
          int cv = static_cast<int>(buffer[i].Event.KeyEvent.wVirtualKeyCode);
          int keyVal = (ca == 0 ? -cv : ca);
          // Skip pure modifier events.
          if (isModifierKey(keyVal)) continue;
          // Remap specific keys.
          if (keyVal == 13) keys.push_back(key::NEWLINE); // Map Enter to newline.
          else if (keyVal == -46) keys.push_back(key::DELETE_KEY);
          else if (keyVal == -49) keys.push_back(static_cast<key>(251));
          // Skip control keys (0–26) except for BACKSPACE, TAB, NEWLINE.
          else if (keyVal >= 0 && keyVal <= 26 && keyVal != static_cast<int>(key::BACKSPACE) &&
                   keyVal != static_cast<int>(key::TAB) && keyVal != static_cast<int>(key::NEWLINE)) {
            continue;
          } else {
            keys.push_back(static_cast<key>(keyVal));
          }
        }
        // (Optionally, key-up events could be processed here to maintain a key state.)
      }
    }
  }
#elif defined(__linux__)
  int nbbytes = 0;
  ioctl(0, FIONREAD, &nbbytes);
  if (nbbytes <= 0) return keys;
  // Set terminal to non-canonical mode and ensure settings are restored automatically.
  TerminalSettings termSettings;
  while (true) {
    ioctl(0, FIONREAD, &nbbytes);
    if (nbbytes <= 0) break;
    int ch = getchar();
    int keyVal = ch;
    if (ch == 27 || ch == 194 || ch == 195) { // potential escape sequences
      int next = getchar();
      if (next == 91) { // '[' following escape.
        int third = getchar();
        if (third == 49) { // F5–F8 sequence.
          int fourth = getchar();
          keyVal = 62 + fourth;
          if (keyVal == 115) keyVal++;
          getchar();              // Discard trailing '~'
        } else if (third == 50) { // Insert or F9–F12 sequence.
          int fourth = getchar();
          if (fourth == 126) keyVal = 45; // Insert key.
          else {
            keyVal = fourth + 71;
            if (keyVal < 121) keyVal++;
            getchar(); // Discard trailing '~'
          }
        } else if (third == 51 || third == 53 || third == 54) {
          getchar(); // Discard trailing '~'
          keyVal = -third;
        }
      } else if (next == 79) { // F1–F4 sequence.
        keyVal = 32 + getchar();
      }
      keyVal = -keyVal;
    }
    // Remap keys to match the key values.
    switch (keyVal) {
    case 127: keyVal = 8; break; // Map delete to backspace.
    case -27: keyVal = 27; break;
    case -51: keyVal = 127; break;
    case -164: keyVal = 132; break; // ä.
    case -182: keyVal = 148; break; // ö.
    case -188: keyVal = 129; break; // ü.
    case -132: keyVal = 142; break; // Ä.
    case -150: keyVal = 153; break; // Ö.
    case -156: keyVal = 154; break; // Ü.
    case -159: keyVal = 225; break; // ß.
    case -181: keyVal = 230; break; // µ.
    case -167: keyVal = 245; break; // §.
    case -176: keyVal = 248; break; // °.
    case -178: keyVal = 253; break; // ².
    case -179: keyVal = 252; break; // ³.
    case -180: keyVal = 239; break; // ´.
    case -65: keyVal = -38; break;  // Up arrow.
    case -66: keyVal = -40; break;  // Down arrow.
    case -68: keyVal = -37; break;  // Left arrow.
    case -67: keyVal = -39; break;  // Right arrow.
    case -53: keyVal = -33; break;  // Page up.
    case -54: keyVal = -34; break;  // Page down.
    case -72: keyVal = -36; break;  // Home.
    case -70: keyVal = -35; break;  // End.
    default: break;
    }
    // Skip any pure modifier events.
    if (isModifierKey(keyVal)) continue;
    // Skip control keys (0–26) except BACKSPACE, TAB, or NEWLINE.
    if (keyVal >= 0 && keyVal <= 26 && keyVal != static_cast<int>(key::BACKSPACE) &&
        keyVal != static_cast<int>(key::TAB) && keyVal != static_cast<int>(key::NEWLINE))
      continue;
    keys.push_back(static_cast<key>(keyVal));
  }
#endif
  return keys;
}

} // namespace Key
} // namespace dcon

#endif // DCON_KEY_HPP
