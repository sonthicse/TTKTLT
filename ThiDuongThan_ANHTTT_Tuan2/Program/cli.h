#ifndef CLI_H
#define CLI_H

#include "constants.h"
#include "utils.h"
#include "book_mgr.h"
#include "book.h"
#include <algorithm>
#include <cctype>
#include <conio.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class CLI
{
public:
	CLI();
	void run();

private:
	int cw;
	int ch;

	vector<string> mItems;
	int curIdx;

	int mAreaW;
	int mBtnL;
	int mBtnW;
	int mStartY;
	int mBtnH;
	int mGap;

	const string tl;
	const string tr;
	const string bl;
	const string br;
	const string h;
	const string v;

	void recalc();

	void drawFrame();
	void drawTitle(const string &text);
	void drawGuide(const string &msg);
	void clrInner();
	void clrContent();

	void drawBox(int left, int top, int width, int height, bool dbl, WORD bc);
	void drawBtn(int left, int top, int width, const string &text, bool sel);

	void drawMMenu();
	void drawMBtn(int idx, bool sel);
	void hlMBtn(int oidx, int nidx);

	void showAdd();
	void showList();
	void showSort();
	void showSearch();
	void showStats();

	void drawLblBox(int left, int top, int bw, const string &lbl,
					const string &val, bool sel);

	int showVMenu(const vector<string> &items, int left, int top, int width);

	string inputLine(int left, int top, int bw, const string &lbl);

	void drawTbl(int left, int top, int page, int rpp);
	void drawPgBtns(int top, int selidx);
};

#endif
