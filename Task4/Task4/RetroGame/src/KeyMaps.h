#pragma once

#include <unordered_map>
#include <utility>

#include <raylib.h>

enum class eGeneralKeys
{
	MENU_UP = 0,
	MENU_DOWN,
	MENU_LEFT,
	MENU_RIGHT,
	MENU_ACCEPT,
	MENU_BACK,
	KEYS_MAX
};
enum class ePongKeys
{
	FIRSTPLAYER_UP = 0,
	FIRSTPLAYER_DOWN,
	SECONDPLAYER_UP,
	SECONDPLAYER_DOWN,
	QUITGAME,
	KEYS_MAX
};
enum class eSnakeKeys
{
	MOVE_UP = 0,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT,
	QUITGAME,
	NEWGAME,
	KEYS_MAX
};

// Not the most elegant approach.
// Stolen from https://gist.github.com/0xD34DC0DE/910855d41786b962127ae401da2a3441
constexpr const char *KeyCodeToString(KeyboardKey keycode) noexcept
{
	switch (keycode)
	{
		case -1: return "NULL";
		case 32: return "Space";
		case 39: return "Apostrophe";
		case 44: return "Comma";
		case 45: return "Minus";
		case 46: return "Period";
		case 47: return "Slash";
		case 48: return "Num0";
		case 49: return "Num1";
		case 50: return "Num2";
		case 51: return "Num3";
		case 52: return "Num4";
		case 53: return "Num5";
		case 54: return "Num6";
		case 55: return "Num7";
		case 56: return "Num8";
		case 57: return "Num9";
		case 59: return "Semicolon";
		case 61: return "Equal";
		case 65: return "A";
		case 66: return "B";
		case 67: return "C";
		case 68: return "D";
		case 69: return "E";
		case 70: return "F";
		case 71: return "G";
		case 72: return "H";
		case 73: return "I";
		case 74: return "J";
		case 75: return "K";
		case 76: return "L";
		case 77: return "M";
		case 78: return "N";
		case 79: return "O";
		case 80: return "P";
		case 81: return "Q";
		case 82: return "R";
		case 83: return "S";
		case 84: return "T";
		case 85: return "U";
		case 86: return "V";
		case 87: return "W";
		case 88: return "X";
		case 89: return "Y";
		case 90: return "Z";
		case 91: return "LeftBracket";
		case 92: return "Backslash";
		case 93: return "RightBracket";
		case 96: return "GraveAccent";
		case 161: return "World1";
		case 162: return "World2";
		case 256: return "Escape";
		case 257: return "Enter";
		case 258: return "Tab";
		case 259: return "Backspace";
		case 260: return "Insert";
		case 261: return "Delete";
		case 262: return "Right";
		case 263: return "Left";
		case 264: return "Down";
		case 265: return "Up";
		case 266: return "PageUp";
		case 267: return "PageDown";
		case 268: return "Home";
		case 269: return "End";
		case 280: return "CapsLock";
		case 281: return "ScrollLock";
		case 282: return "NumLock";
		case 283: return "PrintScreen";
		case 284: return "Pause";
		case 290: return "F1";
		case 291: return "F2";
		case 292: return "F3";
		case 293: return "F4";
		case 294: return "F5";
		case 295: return "F6";
		case 296: return "F7";
		case 297: return "F8";
		case 298: return "F9";
		case 299: return "F10";
		case 300: return "F11";
		case 301: return "F12";
		case 302: return "F13";
		case 303: return "F14";
		case 304: return "F15";
		case 305: return "F16";
		case 306: return "F17";
		case 307: return "F18";
		case 308: return "F19";
		case 309: return "F20";
		case 310: return "F21";
		case 311: return "F22";
		case 312: return "F23";
		case 313: return "F24";
		case 314: return "F25";
		case 320: return "Keypad0";
		case 321: return "Keypad1";
		case 322: return "Keypad2";
		case 323: return "Keypad3";
		case 324: return "Keypad4";
		case 325: return "Keypad5";
		case 326: return "Keypad6";
		case 327: return "Keypad7";
		case 328: return "Keypad8";
		case 329: return "Keypad9";
		case 330: return "KeypadDecimal";
		case 331: return "KeypadDivide";
		case 332: return "KeypadMultiply";
		case 333: return "KeypadSubtract";
		case 334: return "KeypadAdd";
		case 335: return "KeypadEnter";
		case 336: return "KeypadEqual";
		case 340: return "LeftShift";
		case 341: return "LeftControl";
		case 342: return "LeftAlt";
		case 343: return "LeftSuper";
		case 344: return "RightShift";
		case 345: return "RightControl";
		case 346: return "RightAlt";
		case 347: return "RightSuper";
		case 348: return "Menu";
		default: return "NULL";
	};
}
