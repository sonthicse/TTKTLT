#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <windows.h>

const WORD CLR_TXT = 0x0F;
const WORD CLR_ACCENT = 0x0E;
const WORD CLR_FRAME = 0x0B;
const WORD CLR_TITLE = 0x0D;
const WORD CLR_BTN_BORDER = 0x0A;
const WORD CLR_BTN_BORDER_SEL = 0x0E;
const WORD CLR_BTN_TXT = CLR_TXT;
const WORD CLR_BTN_TXT_SEL = 0x4F;
const WORD CLR_BOX_BORDER = CLR_BTN_BORDER;
const WORD CLR_BOX_BORDER_SEL = CLR_BTN_BORDER_SEL;
const WORD CLR_GUIDE_FRAME = CLR_FRAME;
const WORD CLR_GUIDE_LBL = 0x0A;

const std::string TL = "\xE2\x94\x8C";
const std::string TR = "\xE2\x94\x90";
const std::string BL = "\xE2\x94\x94";
const std::string BR = "\xE2\x94\x98";
const std::string H = "\xE2\x94\x80";
const std::string V = "\xE2\x94\x82";

const std::string DBL_TL = "\xE2\x95\x94";
const std::string DBL_TR = "\xE2\x95\x97";
const std::string DBL_BL = "\xE2\x95\x9A";
const std::string DBL_BR = "\xE2\x95\x9D";
const std::string DBL_H = "\xE2\x95\x90";
const std::string DBL_V = "\xE2\x95\x91";

const std::string TBL_T = "\xE2\x94\xAC";
const std::string TBL_B = "\xE2\x94\xB4";
const std::string TBL_L = "\xE2\x94\x9C";
const std::string TBL_R = "\xE2\x94\xA4";
const std::string TBL_X = "\xE2\x94\xBC";

const int MIN_MENU_WIDTH = 24;
const int MIN_BTN_WIDTH = 16;
const int BTN_HEIGHT = 3;
const char UNDERLINE_CHAR = 95;

#endif
