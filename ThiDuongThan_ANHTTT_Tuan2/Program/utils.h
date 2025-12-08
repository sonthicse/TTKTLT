#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <utility>
#include <windows.h>
#include <string>
#include <ctime>
#include <codecvt>
#include <locale>
#include <cwctype>

using namespace std;

void gotoxy(int x, int y);
void setColor(WORD color);
void showCursor(bool visible);
pair<int, int> screenSize();
void clearArea(int left, int top, int width, int height);
bool validDate(int d, int m, int y);
bool validPrice(int price);
void normStr(string &s);

#endif
