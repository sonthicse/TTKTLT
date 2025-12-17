#ifndef UTILS_H
#define UTILS_H

#include "date.h"
#include <codecvt>
#include <ctime>
#include <cwctype>
#include <iostream>
#include <locale>
#include <string>
#include <sstream>
#include <utility>
#include <iomanip>
#include <windows.h>

void gotoXY(int x, int y);
void setColor(WORD color);
void showCursor(bool visible);
std::pair<int, int> getScreenSize();
void clearArea(int left, int top, int width, int height);
bool isValidDate(int d, int m, int y);
bool isValidPrice(int price);

std::string normalizeDisplayName(const std::string &s);
std::string normalizeKey(const std::string &s);
std::string caseFoldUtf8(const std::string &s);
bool containsIgnoreCase(const std::string &haystack, const std::string &needle);

std::string formatDateDDMMYYYY(const class Date &d);
bool parseDateDDMMYYYY(const std::string &s, class Date &out);

#endif
