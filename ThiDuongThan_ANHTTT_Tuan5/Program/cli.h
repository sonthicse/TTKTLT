#ifndef CLI_H
#define CLI_H

#include "utils.h"
#include "book.h"
#include "book_mgr.h"
#include "constants.h"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <conio.h>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

class CLI
{
public:
	CLI();
	void run();

private:
	int cw;
	int ch;

	std::vector<std::string> mItems;
	int curIdx;

	int mAreaW;
	int mBtnL;
	int mBtnW;
	int mStartY;
	int mBtnH;
	int mGap;

	const std::string tl;
	const std::string tr;
	const std::string bl;
	const std::string br;
	const std::string h;
	const std::string v;

	void recalc();

	void drawFrame();
	void drawTitle(const std::string &text);
	void drawGuide(const std::string &msg);
	void clrInner();
	void clrContent();

	void drawBox(int left, int top, int width, int height, bool dbl, WORD bc);
	void drawBtn(int left, int top, int width, const std::string &text, bool sel);

	void drawMMenu();
	void drawMBtn(int idx, bool sel);
	void hlMBtn(int oidx, int nidx);

	void showAdd();
	void showList();
	void showSort();
	void showSearch();
	void showStats();

	void drawLblBox(int left, int top, int bw, const std::string &lbl, const std::string &val, bool sel);

	int showVMenu(const std::vector<std::string> &items, int left, int top, int width);

	std::string inputLine(int left, int top, int bw, const std::string &lbl);

	void drawTbl(int left, int top, int rpp);
	void drawPgBtns(int top, int selidx);

	void showBookTableScreen(const std::string &title, const std::vector<int> &indices, const std::string &subtitleRight);
};

#endif
