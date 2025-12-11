#include "utils.h"

using namespace std;

void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwCursorPosition = {(SHORT)x, (SHORT)y};
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

void setColor(WORD color)
{
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleOutput, color);
}

void showCursor(bool visible)
{
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpConsoleCursorInfo;
	GetConsoleCursorInfo(hConsoleOutput, &lpConsoleCursorInfo);
	lpConsoleCursorInfo.bVisible = visible;
	SetConsoleCursorInfo(hConsoleOutput, &lpConsoleCursorInfo);
}

pair<int, int> screenSize()
{
	pair<int, int> size;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(console, &csbi);
	size.first = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	size.second = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	return size;
}

void clearArea(int left, int top, int width, int height)
{
	string spaces(width, ' ');
	for (int y = top; y < top + height; ++y)
	{
		gotoxy(left, y);
		cout << spaces;
	}
}

static bool isLeap(int y)
{
	return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

bool validDate(int d, int m, int y)
{
	if (m < 1 || m > 12 || d < 1 || y < 0)
		return false;
	int mdays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int days = mdays[m - 1];
	if (m == 2 && isLeap(y))
		days = 29;
	if (d > days)
		return false;
	time_t now = time(nullptr);
	struct tm *tm_now = localtime(&now);
	if (!tm_now)
		return true;
	int cy = tm_now->tm_year + 1900;
	int cm = tm_now->tm_mon + 1;
	int cd = tm_now->tm_mday;
	if (y > cy)
		return false;
	if (y == cy && m > cm)
		return false;
	if (y == cy && m == cm && d > cd)
		return false;
	return true;
}

bool validPrice(int price)
{
	return price >= 0;
}

static wstring toWString(const string &u8)
{
	wstring ws;
	try
	{
		wstring_convert<codecvt_utf8<wchar_t>> conv;
		ws = conv.from_bytes(u8);
	}
	catch (...)
	{
		ws.assign(u8.begin(), u8.end());
	}
	return ws;
}

static string toUTF8(const wstring &ws)
{
	string u8;
	try
	{
		wstring_convert<codecvt_utf8<wchar_t>> conv;
		u8 = conv.to_bytes(ws);
	}
	catch (...)
	{
		u8.assign(ws.begin(), ws.end());
	}
	return u8;
}

void normStr(string &s)
{
	wstring ws = toWString(s);
	for (auto &wc : ws)
		wc = towlower(wc);
	bool capNext = true;
	for (auto &wc : ws)
	{
		if (iswspace(wc))
		{
			capNext = true;
		}
		else if (capNext)
		{
			wc = towupper(wc);
			capNext = false;
		}
	}
	s = toUTF8(ws);
}