#include "utils.h"
#include <string>

using namespace std;

void gotoxy(int x, int y) {
  HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD dwCursorPosition = {(SHORT)x, (SHORT)y};
  SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

void setColor(WORD color) {
  HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsoleOutput, color);
}

void showCursor(bool visible) {
  HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO lpConsoleCursorInfo;
  GetConsoleCursorInfo(hConsoleOutput, &lpConsoleCursorInfo);
  lpConsoleCursorInfo.bVisible = visible;
  SetConsoleCursorInfo(hConsoleOutput, &lpConsoleCursorInfo);
}

pair<int, int> screenSize() {
  pair<int, int> size;
  HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(console, &csbi);
  size.first = csbi.srWindow.Right - csbi.srWindow.Left + 1;
  size.second = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
  return size;
}

void clearArea(int left, int top, int width, int height) {
  string spaces(width, ' ');
  for (int y = top; y < top + height; ++y) {
    gotoxy(left, y);
    cout << spaces;
  }
}
