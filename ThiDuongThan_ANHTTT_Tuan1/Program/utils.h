#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <utility>
#include <windows.h>

using namespace std;

void gotoxy(int x, int y);
void setColor(WORD color);
void showCursor(bool visible);
pair<int, int> screenSize();
void clearArea(int left, int top, int width, int height);

#endif
