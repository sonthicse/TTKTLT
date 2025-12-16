#ifndef UTILS_H
#define UTILS_H

#include <codecvt>
#include <ctime>
#include <cwctype>
#include <iostream>
#include <locale>
#include <string>
#include <utility>
#include <windows.h>

using namespace std;

void gotoxy(int x, int y);
void setColor(WORD color);
void showCursor(bool visible);
pair<int, int> screenSize();
void clearArea(int left, int top, int width, int height);
bool validDate(int d, int m, int y);
bool validPrice(int price);
void normStr(string &s);
string foldLowerUtf8(const string &s);
bool containsFolded(const string &haystack, const string &needle);

#endif
