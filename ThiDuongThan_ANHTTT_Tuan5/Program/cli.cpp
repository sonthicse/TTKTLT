#include "cli.h"

using namespace std;

CLI::CLI()
	: cw(0), ch(0), mItems(), curIdx(0), mAreaW(0), mBtnL(0), mBtnW(0),
	  mStartY(0), mBtnH(BTN_HEIGHT), mGap(0), tl(TL), tr(TR), bl(BL), br(BR),
	  h(H), v(V)
{
	SetConsoleOutputCP(65001);

	mItems.push_back("Them moi ho so sach (M1)");
	mItems.push_back("In danh sach (M2)");
	mItems.push_back("Sap xep (M3)");
	mItems.push_back("Tim kiem (M4)");
	mItems.push_back("Thong ke (M5)");
	mItems.push_back("Thoat (M6)");
}

void CLI::recalc()
{
	auto sz = screenSize();
	cw = sz.first;
	ch = sz.second;

	mAreaW = cw / 4;
	if (mAreaW < MIN_MENU_WIDTH)
		mAreaW = MIN_MENU_WIDTH;

	mBtnL = 2;
	mBtnW = mAreaW - 4;
	if (mBtnW < MIN_BTN_WIDTH)
		mBtnW = MIN_BTN_WIDTH;

	mBtnH = BTN_HEIGHT;
	mGap = 0;

	int totalH = static_cast<int>(mItems.size()) * mBtnH +
				 static_cast<int>(mItems.size() - 1) * mGap;

	mStartY = (ch - totalH) / 2;
	if (mStartY < 3)
		mStartY = 3;
}

void CLI::drawFrame()
{
	setColor(CLR_FRAME);

	gotoxy(0, 0);
	cout << tl;
	gotoxy(cw - 1, 0);
	cout << tr;
	gotoxy(0, ch - 1);
	cout << bl;
	gotoxy(cw - 1, ch - 1);
	cout << br;

	for (int x = 1; x < cw - 1; ++x)
	{
		gotoxy(x, 0);
		cout << h;
		gotoxy(x, ch - 1);
		cout << h;
	}

	for (int y = 1; y < ch - 1; ++y)
	{
		gotoxy(0, y);
		cout << v;
		gotoxy(cw - 1, y);
		cout << v;
	}

	setColor(CLR_TXT);
}

void CLI::drawTitle(const string &text)
{
	setColor(CLR_TXT);
	gotoxy(1, 1);
	for (int i = 1; i < cw - 1; ++i)
		cout << ' ';

	int tx = (cw - static_cast<int>(text.size())) / 2;
	if (tx < 1)
		tx = 1;
	setColor(CLR_TITLE);
	gotoxy(tx, 1);
	cout << text;
	setColor(CLR_TXT);
}

void CLI::drawGuide(const string &msg)
{
	int x = 2;
	int y = ch - 3;
	int w = cw - 4;

	setColor(CLR_GUIDE_FRAME);
	for (int i = x; i < x + w; ++i)
	{
		gotoxy(i, y - 1);
		cout << char(UNDERLINE_CHAR);
	}

	gotoxy(x, y);
	setColor(CLR_TXT);
	for (int i = 0; i < w; ++i)
		cout << ' ';

	gotoxy(x, y);
	setColor(CLR_GUIDE_LBL);
	cout << msg;

	setColor(CLR_TXT);
}

void CLI::clrInner()
{
	int left = 1;
	int top = 1;
	int width = cw - 2;
	int height = ch - 2;

	if (width > 0 && height > 0)
	{
		clearArea(left, top, width, height);
	}
}

void CLI::clrContent()
{
	int startX = mAreaW;
	if (startX < 2)
		startX = 2;

	int startY = 2;
	int endY = ch - 4;

	int width = (cw - 1) - startX;
	int height = endY - startY + 1;

	if (width > 0 && height > 0)
	{
		clearArea(startX, startY, width, height);
	}
}

void CLI::drawBox(int left, int top, int width, int height, bool dbl, WORD bc)
{
	if (width < 2 || height < 2)
		return;
	int iw = width - 2;
	int ih = height - 2;

	const string &bTL = dbl ? DBL_TL : tl;
	const string &bTR = dbl ? DBL_TR : tr;
	const string &bBL = dbl ? DBL_BL : bl;
	const string &bBR = dbl ? DBL_BR : br;
	const string &bH = dbl ? DBL_H : h;
	const string &bV = dbl ? DBL_V : v;

	setColor(bc);

	gotoxy(left, top);
	cout << bTL;
	for (int i = 0; i < iw; ++i)
		cout << bH;
	cout << bTR;

	for (int y = 0; y < ih; ++y)
	{
		gotoxy(left, top + 1 + y);
		cout << bV;
		gotoxy(left + width - 1, top + 1 + y);
		cout << bV;
	}

	gotoxy(left, top + height - 1);
	cout << bBL;
	for (int i = 0; i < iw; ++i)
		cout << bH;
	cout << bBR;

	setColor(CLR_TXT);
}

void CLI::drawBtn(int left, int top, int width, const string &text, bool sel)
{
	if (width < 4)
		return;

	WORD bc = sel ? CLR_BTN_BORDER_SEL : CLR_BTN_BORDER;
	drawBox(left, top, width, 3, true, bc);

	int iw = width - 2;
	int tlen = static_cast<int>(text.size());
	if (tlen > iw)
		tlen = iw;
	int toff = (iw - tlen) / 2;
	int tx = left + 1 + toff;

	WORD tc = sel ? CLR_BTN_TXT_SEL : CLR_BTN_TXT;

	setColor(tc);
	gotoxy(left + 1, top + 1);
	for (int i = 0; i < iw; ++i)
		cout << ' ';

	gotoxy(tx, top + 1);
	cout << text.substr(0, tlen);

	setColor(CLR_TXT);
}

void CLI::drawMBtn(int idx, bool sel)
{
	int left = mBtnL;
	int width = mBtnW;
	int top = mStartY + idx * (mBtnH + mGap);

	drawBtn(left, top, width, mItems[idx], sel);
}

void CLI::drawMMenu()
{
	for (int i = 0; i < static_cast<int>(mItems.size()); ++i)
	{
		bool sel = (i == curIdx);
		drawMBtn(i, sel);
	}
}

void CLI::hlMBtn(int oidx, int nidx)
{
	if (oidx >= 0 && oidx < static_cast<int>(mItems.size()))
	{
		drawMBtn(oidx, false);
	}
	if (nidx >= 0 && nidx < static_cast<int>(mItems.size()))
	{
		drawMBtn(nidx, true);
	}
}

void CLI::drawLblBox(int left, int top, int bw, const string &lbl,
					 const string &val, bool sel)
{
	setColor(CLR_ACCENT);
	gotoxy(left, top);
	cout << lbl;

	int bl = left;
	int bt = top + 1;

	WORD bc = sel ? CLR_BOX_BORDER_SEL : CLR_BOX_BORDER;
	drawBox(bl, bt, bw, 3, true, bc);

	int iw = bw - 2;
	setColor(CLR_TXT);
	string clipped = val;
	if (static_cast<int>(clipped.size()) > iw)
	{
		clipped = clipped.substr(0, iw);
	}

	gotoxy(bl + 1, bt + 1);
	cout << clipped;
	for (int i = 0; i < iw - static_cast<int>(clipped.size()); ++i)
	{
		cout << ' ';
	}
}

int CLI::showVMenu(const vector<string> &items, int left, int top, int width)
{
	if (items.empty())
		return -1;

	int cidx = 0;
	int step = mBtnH + mGap;
	if (step <= 0)
		step = mBtnH;

	while (true)
	{
		int y = top;
		for (int i = 0; i < static_cast<int>(items.size()); ++i)
		{
			drawBtn(left, y, width, items[i], i == cidx);
			y += step;
		}

		int c = _getch();
		if (c == 27)
		{
			return -1;
		}
		else if (c == 13)
		{
			return cidx;
		}
		else if (c == 224 || c == 0)
		{
			int c2 = _getch();
			if (c2 == 72)
			{
				cidx--;
				if (cidx < 0)
					cidx = static_cast<int>(items.size()) - 1;
			}
			else if (c2 == 80)
			{
				cidx++;
				if (cidx >= static_cast<int>(items.size()))
					cidx = 0;
			}
		}
	}
}

string CLI::inputLine(int left, int top, int bw, const string &lbl)
{
	string val;
	bool done = false;

	int iw = bw - 2;
	if (iw < 1)
		iw = 1;

	while (!done)
	{
		drawLblBox(left, top, bw, lbl, val, true);

		int tlen = static_cast<int>(val.size());
		if (tlen > iw)
			tlen = iw;

		int cc = left + 1 + tlen;
		int cr = top + 2;
		gotoxy(cc, cr);

		int c = _getch();
		if (c == 27)
		{
			val.clear();
			done = true;
		}
		else if (c == 13)
		{
			done = true;
		}
		else if (c == 8)
		{
			if (!val.empty())
				val.pop_back();
		}
		else if (isprint(c))
		{
			if (static_cast<int>(val.size()) < iw)
			{
				val.push_back(static_cast<char>(c));
			}
		}
	}

	return val;
}

void CLI::showAdd()
{
	recalc();
	clrInner();
	drawTitle("THEM MOI HO SO SACH (M1)");
	drawGuide("Huong dan: Nhap gia tri va nhan Enter. Esc de huy.");

	vector<string> lbls = {"Ma the loai:",
						   "Ma sach (ISBN):",
						   "Ten sach:",
						   "Tac gia:",
						   "Ngay nhap kho (dd/mm/yyyy):",
						   "Gia sach:"};
	vector<string> values(lbls.size());

	int bw = cw - 10;
	if (bw > 60)
		bw = 60;
	if (bw < 20)
		bw = 20;
	int fh = (int(lbls.size()) - 1) * 4 + 3;
	int ft = (ch - fh) / 2;
	if (ft < 3)
		ft = 3;
	if (ft + fh > ch - 5)
		ft = ch - 5 - fh;
	int fl = (cw - bw) / 2;
	if (fl < 4)
		fl = 4;
	vector<int> tops(lbls.size());
	int y = ft;
	for (size_t i = 0; i < lbls.size(); ++i)
	{
		tops[i] = y;
		y += 4;
	}

	auto drawFields = [&](int current)
	{
		for (size_t i = 0; i < lbls.size(); ++i)
		{
			bool sel = (int(i) == current);
			drawLblBox(fl, tops[i], bw, lbls[i], values[i], sel);
		}
	};

	for (int idx = 0; idx < (int)lbls.size(); ++idx)
	{
		bool ok = false;
		while (!ok)
		{
			drawFields(idx);
			string val = inputLine(fl, tops[idx], bw, lbls[idx]);
			if (val.empty())
				return;
			ok = true;
			if (idx == 4)
			{
				int d = 0, m = 0, yv = 0;
				char sep;
				stringstream ss(val);
				if (!(ss >> d >> sep >> m >> sep >> yv) || sep != '/' ||
					!validDate(d, m, yv))
				{
					ok = false;
					drawGuide("Ngay khong hop le. Dinh dang dd/mm/yyyy va khong vuot qua "
							  "ngay hien tai.");
				}
			}
			else if (idx == 5)
			{
				try
				{
					int price = stoi(val);
					if (!validPrice(price))
					{
						ok = false;
						drawGuide("Gia sach phai la so nguyen khong am.");
					}
				}
				catch (...)
				{
					ok = false;
					drawGuide("Gia sach phai la so nguyen.");
				}
			}
			else
			{
				bool empty = true;
				for (char c : val)
				{
					if (!isspace((unsigned char)c))
					{
						empty = false;
						break;
					}
				}
				if (empty)
				{
					ok = false;
					drawGuide("Truong khong duoc de trong.");
				}
			}
			if (ok)
			{
				if (idx == 2 || idx == 3)
					normStr(val);
				values[idx] = val;
			}
		}
	}

	Book b;
	b.setMaTL(values[0]);
	b.setISBN(values[1]);
	b.setTenSach(values[2]);
	b.setTacGia(values[3]);
	int d, m, yv;
	char sep;
	stringstream ss(values[4]);
	ss >> d >> sep >> m >> sep >> yv;
	b.setNgayNhap(Date(d, m, yv));
	b.setGiaSach(stoi(values[5]));
	if (BookMgr::get().add(b))
	{
		drawGuide("Them sach thanh cong. Nhan phim bat ky de quay lai MENU.");
	}
	else
	{
		drawGuide("Loi khi ghi file. Nhan phim bat ky de quay lai MENU.");
	}
	_getch();
}

void CLI::drawTbl(int tl, int tt, int rpp)
{
	int wSTT = 4;
	int wMaTL = 6;
	int wMaSach = 13;
	int wNgay = 10;
	int wGia = 11;

	int avail = cw - 4;
	if (avail < 90)
		avail = 90;
	int extra = avail - 90;

	int wTen = 20 + (int)(extra * 0.55);
	int wTacGia = 18 + (int)(extra * 0.45);

	int widths[] = {wSTT, wMaTL, wMaSach, wTen, wTacGia, wNgay, wGia};
	int ccnt = 7;

	auto drawBRow = [&](int y, const string &lc, const string &mc,
						const string &rc)
	{
		gotoxy(tl, y);
		setColor(CLR_BTN_BORDER_SEL);
		cout << lc;
		for (int c = 0; c < ccnt; ++c)
		{
			for (int i = 0; i < widths[c]; ++i)
				cout << H;
			cout << (c == ccnt - 1 ? rc : mc);
		}
	};

	drawBRow(tt, TL, TBL_T, TR);

	setColor(CLR_BTN_BORDER_SEL);
	gotoxy(tl, tt + 1);
	cout << V;

	const char *hdrs[] = {"STT", "Ma TL", "Ma sach", "Ten sach",
						  "Tac gia", "Ngay nhap", "Gia"};
	for (int i = 0; i < ccnt; ++i)
	{
		setColor(CLR_TITLE);
		cout << left << setw(widths[i]) << hdrs[i];
		setColor(CLR_BTN_BORDER_SEL);
		cout << V;
	}

	drawBRow(tt + 2, TBL_L, TBL_X, TBL_R);

	int y = tt + 3;
	for (int row = 0; row < rpp; ++row)
	{
		if (row > 0)
		{
			drawBRow(y, TBL_L, TBL_X, TBL_R);
			++y;
		}

		gotoxy(tl, y);
		setColor(CLR_BTN_BORDER_SEL);
		cout << V;
		for (int c = 0; c < ccnt; ++c)
		{
			for (int i = 0; i < widths[c]; ++i)
				cout << ' ';
			cout << V;
		}
		++y;
	}

	drawBRow(y, BL, TBL_B, BR);
	setColor(CLR_TXT);
}

void CLI::drawPgBtns(int top, int selidx)
{
	int bw = 19;
	int gap = 4;
	int tw = 3 * bw + 2 * gap;

	int left = (cw - tw) / 2;
	if (left < 2)
		left = 2;

	drawBtn(left, top, bw, "←", selidx == 0);
	drawBtn(left + bw + gap, top, bw, "→", selidx == 1);
	drawBtn(left + 2 * (bw + gap), top, bw, "Tro ve", selidx == 2);
}

void CLI::showList()
{
	recalc();
	clrInner();
	drawTitle("DANH SACH SACH (M2)");
	drawGuide("Huong dan: [↑]/[↓] Chon hang | ← / → Chon nut | [Enter]: Xac nhan "
			  "| [Esc]: MENU");

	int availH = ch - 14;
	int rpp = max(1, availH / 2);

	int wSTT = 4, wMaTL = 6, wMaSach = 13, wNgay = 10, wGia = 11;
	int availW = max(90, cw - 4);
	int extra = availW - 90;
	int wTen = 20 + (int)(extra * 0.55);
	int wTacGia = 18 + (int)(extra * 0.45);

	int widths[] = {wSTT, wMaTL, wMaSach, wTen, wTacGia, wNgay, wGia};
	int tw = 1;
	for (int w : widths)
		tw += w + 1;

	int th = rpp * 2 + 3;
	int bh = th + 3;
	int tt = max(3, (ch - bh) / 2);
	if (tt + bh > ch - 3)
		tt = ch - 3 - bh;

	int btnsT = tt + th;
	int tl = max(2, (cw - tw) / 2);

	BookMgr::get().load();
	const auto &list = BookMgr::get().getList();
	int totalRows = (int)list.size();
	int totalPages = max(1, (totalRows + rpp - 1) / rpp);

	auto drawRow = [&](int idx, int rowY, bool sel)
	{
		if (idx < 0 || idx >= totalRows)
			return;

		const Book &bk = list[idx];
		WORD rowColor = sel ? CLR_BTN_TXT_SEL : CLR_TXT;
		setColor(rowColor);

		int cx = tl + 1;
		gotoxy(cx, rowY);
		cout << left << setw(wSTT) << (idx + 1);
		cx += wSTT + 1;

		gotoxy(cx, rowY);
		cout << left << setw(wMaTL) << bk.getMaTL().substr(0, wMaTL);
		cx += wMaTL + 1;

		gotoxy(cx, rowY);
		cout << left << setw(wMaSach) << bk.getISBN().substr(0, wMaSach);
		cx += wMaSach + 1;

		gotoxy(cx, rowY);
		cout << left << setw(wTen) << bk.getTenSach().substr(0, wTen);
		cx += wTen + 1;

		gotoxy(cx, rowY);
		cout << left << setw(wTacGia) << bk.getTacGia().substr(0, wTacGia);
		cx += wTacGia + 1;

		gotoxy(cx, rowY);
		Date d = bk.getNgayNhap();
		stringstream ds;
		ds << setfill('0') << setw(2) << d.getDay() << "/" << setw(2)
		   << d.getMonth() << "/" << setw(4) << d.getYear();
		cout << left << setw(wNgay) << ds.str().substr(0, wNgay);
		cx += wNgay + 1;

		gotoxy(cx, rowY);
		cout << right << setw(wGia) << bk.getGiaSach();
	};

	int page = 0;
	int selBtn = 1;
	int selRow = (totalRows > 0) ? 0 : -1;
	bool inScr = true;
	bool redrawT = true;
	bool redrawB = true;

	while (inScr)
	{
		if (redrawT)
		{
			setColor(CLR_TXT);
			gotoxy(2, 2);
			for (int i = 0; i < cw - 4; ++i)
				cout << ' ';

			string pgInfo =
				"Trang " + to_string(page + 1) + "/" + to_string(totalPages);
			int pgX = max(2, cw - (int)pgInfo.size() - 3);
			setColor(CLR_ACCENT);
			gotoxy(pgX, 2);
			cout << pgInfo;
			setColor(CLR_TXT);

			drawTbl(tl, tt, rpp);
			int startRow = page * rpp;
			int rowY = tt + 3;
			for (int r = 0; r < rpp; ++r)
			{
				int idx = startRow + r;
				if (idx >= totalRows)
					break;

				bool sel = (idx == selRow);
				drawRow(idx, rowY, sel);
				rowY += 2;
			}
			setColor(CLR_TXT);
			redrawT = false;
		}

		if (redrawB)
		{
			drawPgBtns(btnsT, selBtn);
			redrawB = false;
		}

		int c = _getch();
		if (c == 27)
		{
			inScr = false;
		}
		else if (c == 13)
		{
			if (selBtn == 0 && page > 0)
			{
				page--;
				if (totalRows > 0)
				{
					selRow = page * rpp;
					if (selRow >= totalRows)
						selRow = totalRows - 1;
				}
				redrawT = true;
			}
			else if (selBtn == 1 && page < totalPages - 1)
			{
				page++;
				if (totalRows > 0)
				{
					selRow = page * rpp;
					if (selRow >= totalRows)
						selRow = totalRows - 1;
				}
				redrawT = true;
			}
			else if (selBtn == 2)
			{
				inScr = false;
			}
		}
		else if (c == 224 || c == 0)
		{
			int c2 = _getch();
			if (c2 == 75)
			{
				selBtn = (selBtn - 1 + 3) % 3;
				redrawB = true;
			}
			else if (c2 == 77)
			{
				selBtn = (selBtn + 1) % 3;
				redrawB = true;
			}
			else if (c2 == 72)
			{
				if (selRow > 0)
				{
					int oldRow = selRow;
					selRow--;

					if (selRow < page * rpp)
					{
						if (page > 0)
							page--;
						redrawT = true;
					}
					else
					{
						int startRow = page * rpp;
						int oldOffset = oldRow - startRow;
						int newOffset = selRow - startRow;
						int oldY = tt + 3 + oldOffset * 2;
						int newY = tt + 3 + newOffset * 2;

						drawRow(oldRow, oldY, false);
						drawRow(selRow, newY, true);
						setColor(CLR_TXT);
					}
				}
			}
			else if (c2 == 80)
			{
				if (selRow >= 0 && selRow < totalRows - 1)
				{
					int oldRow = selRow;
					selRow++;

					if (selRow >= (page + 1) * rpp)
					{
						if (page < totalPages - 1)
							page++;
						redrawT = true;
					}
					else
					{
						int startRow = page * rpp;
						int oldOffset = oldRow - startRow;
						int newOffset = selRow - startRow;
						int oldY = tt + 3 + oldOffset * 2;
						int newY = tt + 3 + newOffset * 2;

						drawRow(oldRow, oldY, false);
						drawRow(selRow, newY, true);
						setColor(CLR_TXT);
					}
				}
			}
		}
	}
}

void CLI::showSort()
{
	clrContent();
	drawTitle("SAP XEP (M3)");
	drawGuide(
		"Huong dan: [↑]/[↓] chon | [Enter]: xac nhan | [Esc]: quay lai MENU");

	// Định nghĩa các thuật toán sắp xếp mà người dùng có thể chọn. Chỉ các thuật
	// toán có triển khai trong BookMgr mới được liệt kê ở đây.
	vector<string> algos = {"Insertion sort", "Quick sort", "Merge sort",
							"Heap sort"};
	// Định nghĩa các tiêu chí sắp xếp. Các tùy chọn bổ sung như danh mục và sắp
	// xếp đa cấp (MaTL -> Ten -> Ngay) được cung cấp.
	vector<string> keys = {"Ma sach (ISBN)",
						   "Ten sach",
						   "Tac gia",
						   "Ngay nhap kho",
						   "Gia sach",
						   "Ma the loai",
						   "Da tieu chi (MaTL -> Ten -> Ngay)"};

	int sw1 = 30, sw2 = 30;
	for (const auto &s : algos)
		sw1 = max(sw1, (int)s.size() + 4);
	for (const auto &s : keys)
		sw2 = max(sw2, (int)s.size() + 4);

	const int GAP = 4;
	int sx = mBtnL + mBtnW + GAP;
	int avail = cw - 2 - sx;

	if (avail > 0)
	{
		int maxW = (avail - GAP) / 2;
		if (maxW < 20)
			maxW = 20;
		if (sw1 > maxW)
			sw1 = maxW;
		if (sw2 > maxW)
			sw2 = maxW;
	}

	int tw = sw1 + GAP + sw2;
	if (sx + tw > cw - 2)
	{
		sx = max(mBtnL + mBtnW + 2, cw - 2 - tw);
	}

	int l1 = sx;
	int l2 = l1 + sw1 + GAP;

	int cnt = max((int)algos.size(), (int)keys.size());
	int height = cnt * mBtnH + (cnt - 1) * mGap;
	int top = max(3, (ch - height) / 2);
	if (top + height > ch - 5)
		top = ch - 5 - height;

	setColor(CLR_ACCENT);
	gotoxy(l1, top - 2);
	cout << "Chon thuat toan sap xep:";
	int aidx = showVMenu(algos, l1, top, sw1);
	if (aidx < 0)
		return;

	setColor(CLR_ACCENT);
	gotoxy(l2, top - 2);
	cout << "Chon khoa sap xep:";
	int kidx = showVMenu(keys, l2, top, sw2);
	if (kidx < 0)
		return;

	// Sau khi cả thuật toán và tiêu chí được chọn, hãy thực hiện sắp xếp.
	BookMgr::SortAlgorithm algorithm;
	switch (aidx)
	{
	case 0:
		algorithm = BookMgr::SortAlgorithm::Insertion;
		break;
	case 1:
		algorithm = BookMgr::SortAlgorithm::Quick;
		break;
	case 2:
		algorithm = BookMgr::SortAlgorithm::Merge;
		break;
	case 3:
		algorithm = BookMgr::SortAlgorithm::Heap;
		break;
	default:
		algorithm = BookMgr::SortAlgorithm::Insertion;
		break;
	}
	// Ánh xạ chỉ mục tiêu chí tới BookMgr::SortCriteria.
	BookMgr::SortCriteria criteria;
	switch (kidx)
	{
	case 0:
		criteria = BookMgr::SortCriteria::ISBN;
		break;
	case 1:
		criteria = BookMgr::SortCriteria::Title;
		break;
	case 2:
		criteria = BookMgr::SortCriteria::Author;
		break;
	case 3:
		criteria = BookMgr::SortCriteria::Date;
		break;
	case 4:
		criteria = BookMgr::SortCriteria::Price;
		break;
	case 5:
		criteria = BookMgr::SortCriteria::Category;
		break;
	case 6:
		criteria = BookMgr::SortCriteria::Multi;
		break;
	default:
		criteria = BookMgr::SortCriteria::ISBN;
		break;
	}
	// Gọi sắp xếp thông qua BookMgr::sortList. Sẽ cập nhật cả danh sách trong bộ
	// nhớ và tệp dữ liệu cơ bản.
	BookMgr::get().sortList(algorithm, criteria);
	// Hiển thị danh sách đã sắp xếp bằng chức năng liệt kê hiện có. Hàm showList
	// tải từ tệp, do đó thứ tự mới sẽ được in ra màn hình.
	showList();
	return;
}

void CLI::showSearch()
{
	clrContent();
	drawTitle("TIM KIEM (M4)");
	drawGuide(
		"Huong dan: [↑]/[↓] chon | [Enter]: xac nhan | [Esc]: quay lai MENU");

	// Bước 1: Chọn thuật toán
	vector<string> algos = {"Tim kiem tuan tu", "Tim kiem nhi phan"};
	int sw1 = 30;
	for (const auto &s : algos)
		sw1 = max(sw1, (int)s.size() + 4);

	const int GAP = 4;
	int sx = mBtnL + mBtnW + GAP;
	if (sw1 > cw - sx - 4)
		sw1 = cw - sx - 4;

	int cnt = (int)algos.size();
	int height = cnt * mBtnH + (cnt - 1) * mGap;
	int top = max(3, (ch - height) / 2);

	setColor(CLR_ACCENT);
	gotoxy(sx, top - 2);
	cout << "Chon thuat toan tim kiem:";
	int aidx = showVMenu(algos, sx, top, sw1);
	if (aidx < 0)
		return;

	// Bước 2: Chọn kiểu tìm kiếm
	clrContent();
	drawTitle("TIM KIEM (M4)");
	drawGuide(
		"Huong dan: [↑]/[↓] chon | [Enter]: xac nhan | [Esc]: quay lai MENU");

	vector<string> searchTypes = {"Chinh xac", "Khong chinh xac",
								  "Khong xac dinh truong"};
	int sw2 = 40;
	for (const auto &s : searchTypes)
		sw2 = max(sw2, (int)s.size() + 4);
	if (sw2 > cw - sx - 4)
		sw2 = cw - sx - 4;

	cnt = (int)searchTypes.size();
	height = cnt * mBtnH + (cnt - 1) * mGap;
	top = max(3, (ch - height) / 2);

	setColor(CLR_ACCENT);
	gotoxy(sx, top - 2);
	cout << "Chon kieu tim kiem:";
	int tidx = showVMenu(searchTypes, sx, top, sw2);
	if (tidx < 0)
		return;

	// Kiểm tra: Binary chỉ áp dụng cho Exact
	bool useBinary = (aidx == 1);
	if (useBinary && tidx != 0)
	{
		// Chuyển sang tuần tự và thông báo
		useBinary = false;
		clrContent();
		drawTitle("TIM KIEM (M4)");
		drawGuide("Nhi phan chi ap dung tim chinh xac -> chuyen sang tuan tu. Nhan "
				  "phim bat ky.");
		_getch();
	}

	// Bước 3: Chọn khóa (chỉ khi không phải Global)
	int kidx = 0;
	if (tidx != 2) // Không phải Global
	{
		clrContent();
		drawTitle("TIM KIEM (M4)");
		drawGuide(
			"Huong dan: [↑]/[↓] chon | [Enter]: xac nhan | [Esc]: quay lai MENU");

		vector<string> keys = {"Ma the loai", "Ma sach (ISBN)", "Ten sach",
							   "Tac gia"};
		int sw3 = 30;
		for (const auto &s : keys)
			sw3 = max(sw3, (int)s.size() + 4);
		if (sw3 > cw - sx - 4)
			sw3 = cw - sx - 4;

		cnt = (int)keys.size();
		height = cnt * mBtnH + (cnt - 1) * mGap;
		top = max(3, (ch - height) / 2);

		setColor(CLR_ACCENT);
		gotoxy(sx, top - 2);
		cout << "Chon khoa tim kiem:";
		kidx = showVMenu(keys, sx, top, sw3);
		if (kidx < 0)
			return;
	}

	// Bước 4: Nhập chuỗi tìm kiếm
	clrContent();
	drawTitle("TIM KIEM (M4)");
	drawGuide("Nhap gia tri tim kiem | [Enter]: xac nhan | [Esc]: huy");

	int bw = cw / 3;
	if (bw < 20)
		bw = 20;
	if (bw > cw - mAreaW - 8)
		bw = cw - mAreaW - 8;

	int left = mBtnL + mBtnW + 4;
	if (left + bw > cw - 2)
		left = cw - 2 - bw;

	int topBox = max(4, ch / 2 - 2);
	string kval = inputLine(left, topBox, bw, "Gia tri tim kiem:");

	if (kval.empty())
		return; // User nhấn ESC

	// Bước 5: Thực hiện tìm kiếm
	BookMgr::SortCriteria criteria;
	switch (kidx)
	{
	case 0:
		criteria = BookMgr::SortCriteria::Category;
		break;
	case 1:
		criteria = BookMgr::SortCriteria::ISBN;
		break;
	case 2:
		criteria = BookMgr::SortCriteria::Title;
		break;
	case 3:
		criteria = BookMgr::SortCriteria::Author;
		break;
	default:
		criteria = BookMgr::SortCriteria::ISBN;
		break;
	}

	vector<int> matchIndices;

	if (tidx == 0) // Exact
	{
		if (useBinary)
			matchIndices = BookMgr::get().searchExactBinary(criteria, kval);
		else
			matchIndices = BookMgr::get().searchExactLinear(criteria, kval);
	}
	else if (tidx == 1) // Contains
	{
		matchIndices = BookMgr::get().searchContainsLinear(criteria, kval);
	}
	else // Global
	{
		matchIndices = BookMgr::get().searchGlobalLinear(kval);
	}

	// Bước 6: Hiển thị kết quả
	if (matchIndices.empty())
	{
		clrInner();
		drawTitle("TIM KIEM (M4) - KET QUA");
		drawGuide("Khong tim thay ket qua nao. Nhan phim bat ky de quay lai MENU.");
		_getch();
		return;
	}

	// Hiển thị màn hình kết quả - CHỈ hiển thị các kết quả tìm thấy
	showSearchResults(matchIndices, kval, criteria, tidx);
}

// Hàm helper hiển thị kết quả tìm kiếm (thêm vào CLI private hoặc đây)
// Hàm hiển thị kết quả tìm kiếm - CHỈ hiển thị các sách được tìm thấy
void CLI::showSearchResults(const vector<int> &matchIndices,
							const string &searchTerm,
							BookMgr::SortCriteria searchCriteria,
							int searchTypeIdx)
{
	recalc();
	clrInner();
	drawTitle("TIM KIEM (M4) - KET QUA");
	drawGuide("Huong dan: [↑]/[↓] Chon hang | ← / → Chon nut | [Enter]: Xac nhan "
			  "| [Esc]: MENU");

	int availH = ch - 14;
	int rpp = max(1, availH / 2);

	int wSTT = 4, wMaTL = 6, wMaSach = 13, wNgay = 10, wGia = 11;
	int availW = max(90, cw - 4);
	int extra = availW - 90;
	int wTen = 20 + (int)(extra * 0.55);
	int wTacGia = 18 + (int)(extra * 0.45);

	int widths[] = {wSTT, wMaTL, wMaSach, wTen, wTacGia, wNgay, wGia};
	int tw = 1;
	for (int w : widths)
		tw += w + 1;

	int th = rpp * 2 + 3;
	int bh = th + 3;
	int tt = max(3, (ch - bh) / 2);
	if (tt + bh > ch - 3)
		tt = ch - 3 - bh;

	int btnsT = tt + th;
	int tl = max(2, (cw - tw) / 2);

	BookMgr::get().load();
	const auto &fullList = BookMgr::get().getList();

	// CHỈ lấy các sách được tìm thấy
	vector<Book> resultBooks;
	for (int idx : matchIndices)
	{
		if (idx >= 0 && idx < (int)fullList.size())
			resultBooks.push_back(fullList[idx]);
	}

	int totalRows = (int)resultBooks.size();
	int totalPages = max(1, (totalRows + rpp - 1) / rpp);

	// Hàm vẽ một dòng kết quả
	auto drawRow = [&](int resultIdx, int rowY, bool sel)
	{
		if (resultIdx < 0 || resultIdx >= totalRows)
			return;

		const Book &bk = resultBooks[resultIdx];
		WORD rowColor = sel ? CLR_BTN_TXT_SEL : CLR_TXT;
		setColor(rowColor);

		int cx = tl + 1;
		gotoxy(cx, rowY);
		cout << left << setw(wSTT) << (resultIdx + 1);
		cx += wSTT + 1;

		gotoxy(cx, rowY);
		cout << left << setw(wMaTL) << bk.getMaTL().substr(0, wMaTL);
		cx += wMaTL + 1;

		gotoxy(cx, rowY);
		cout << left << setw(wMaSach) << bk.getISBN().substr(0, wMaSach);
		cx += wMaSach + 1;

		gotoxy(cx, rowY);
		cout << left << setw(wTen) << bk.getTenSach().substr(0, wTen);
		cx += wTen + 1;

		gotoxy(cx, rowY);
		cout << left << setw(wTacGia) << bk.getTacGia().substr(0, wTacGia);
		cx += wTacGia + 1;

		gotoxy(cx, rowY);
		Date d = bk.getNgayNhap();
		stringstream ds;
		ds << setfill('0') << setw(2) << d.getDay() << "/" << setw(2)
		   << d.getMonth() << "/" << setw(4) << d.getYear();
		cout << left << setw(wNgay) << ds.str().substr(0, wNgay);
		cx += wNgay + 1;

		gotoxy(cx, rowY);
		cout << right << setw(wGia) << bk.getGiaSach();
	};

	int page = 0;
	int selRow = (totalRows > 0) ? 0 : -1;
	int selBtn = 1;
	bool inScr = true;
	bool redrawT = true;
	bool redrawB = true;

	while (inScr)
	{
		if (redrawT)
		{
			setColor(CLR_TXT);
			gotoxy(2, 2);
			for (int i = 0; i < cw - 4; ++i)
				cout << ' ';

			string pgInfo = "Trang " + to_string(page + 1) + "/" +
							to_string(totalPages) +
							" | Tim thay: " + to_string(totalRows);
			int pgX = max(2, cw - (int)pgInfo.size() - 3);
			setColor(CLR_ACCENT);
			gotoxy(pgX, 2);
			cout << pgInfo;
			setColor(CLR_TXT);

			drawTbl(tl, tt, rpp);
			int startRow = page * rpp;
			int rowY = tt + 3;
			for (int r = 0; r < rpp; ++r)
			{
				int idx = startRow + r;
				if (idx >= totalRows)
					break;

				bool sel = (idx == selRow);
				drawRow(idx, rowY, sel);
				rowY += 2;
			}
			setColor(CLR_TXT);
			redrawT = false;
		}

		if (redrawB)
		{
			drawPgBtns(btnsT, selBtn);
			redrawB = false;
		}

		int c = _getch();
		if (c == 27)
		{
			inScr = false;
		}
		else if (c == 13)
		{
			if (selBtn == 0 && page > 0)
			{
				page--;
				if (totalRows > 0)
				{
					selRow = page * rpp;
					if (selRow >= totalRows)
						selRow = totalRows - 1;
				}
				redrawT = true;
			}
			else if (selBtn == 1 && page < totalPages - 1)
			{
				page++;
				if (totalRows > 0)
				{
					selRow = page * rpp;
					if (selRow >= totalRows)
						selRow = totalRows - 1;
				}
				redrawT = true;
			}
			else if (selBtn == 2)
			{
				inScr = false;
			}
		}
		else if (c == 224 || c == 0)
		{
			int c2 = _getch();
			if (c2 == 75) // Left
			{
				selBtn = (selBtn - 1 + 3) % 3;
				redrawB = true;
			}
			else if (c2 == 77) // Right
			{
				selBtn = (selBtn + 1) % 3;
				redrawB = true;
			}
			else if (c2 == 72) // Up
			{
				if (selRow > 0)
				{
					int oldRow = selRow;
					selRow--;

					if (selRow < page * rpp)
					{
						if (page > 0)
							page--;
						redrawT = true;
					}
					else
					{
						int startRow = page * rpp;
						int oldOffset = oldRow - startRow;
						int newOffset = selRow - startRow;
						int oldY = tt + 3 + oldOffset * 2;
						int newY = tt + 3 + newOffset * 2;

						drawRow(oldRow, oldY, false);
						drawRow(selRow, newY, true);
						setColor(CLR_TXT);
					}
				}
			}
			else if (c2 == 80) // Down
			{
				if (selRow >= 0 && selRow < totalRows - 1)
				{
					int oldRow = selRow;
					selRow++;

					if (selRow >= (page + 1) * rpp)
					{
						if (page < totalPages - 1)
							page++;
						redrawT = true;
					}
					else
					{
						int startRow = page * rpp;
						int oldOffset = oldRow - startRow;
						int newOffset = selRow - startRow;
						int oldY = tt + 3 + oldOffset * 2;
						int newY = tt + 3 + newOffset * 2;

						drawRow(oldRow, oldY, false);
						drawRow(selRow, newY, true);
						setColor(CLR_TXT);
					}
				}
			}
		}
	}
}

void CLI::showStats()
{
	clrContent();
	drawTitle("THONG KE (M5)");
	drawGuide(
		"Huong dan: [↑]/[↓] chon | [Enter]: xac nhan | [Esc]: quay lai MENU");

	vector<string> opts = {"So luong sach theo the loai",
						   "Ty le sach theo khoang gia",
						   "Tong gia tri sach theo the loai"};

	int sw = 40;
	for (const auto &s : opts)
		sw = max(sw, (int)s.size() + 4);
	if (sw > cw / 3)
		sw = cw / 3;

	int cnt = (int)opts.size();
	int sh = cnt * mBtnH + (cnt - 1) * mGap;
	int top = max(3, (ch - sh) / 2);
	if (top + sh > ch - 5)
		top = ch - 5 - sh;

	int left = min(cw - 2 - sw, mBtnL + mBtnW + 4);

	setColor(CLR_ACCENT);
	gotoxy(left, top - 2);
	cout << "Chon loai bao cao / thong ke:";

	int oidx = showVMenu(opts, left, top, sw);
	if (oidx < 0)
		return;

	clrInner();
	drawTitle("THONG KE (M5)");
	drawGuide("Nhan phim bat ky de quay lai MENU chinh.");

	_getch();
}

void CLI::run()
{
	recalc();
	BookMgr::get().load();
	drawFrame();
	clrInner();
	drawTitle("CHUONG TRINH QUAN LY SACH THU VIEN");
	drawMMenu();
	drawGuide(
		"Huong dan: [↑] Len | [↓] Xuong | [Enter]: Xac nhan | [Esc]: Thoat");

	showCursor(false);

	bool running = true;
	while (running)
	{
		int c = _getch();

		if (c == 224 || c == 0)
		{
			int c2 = _getch();
			if (c2 == 72)
			{
				int old = curIdx;
				curIdx = (curIdx - 1 + mItems.size()) % mItems.size();
				hlMBtn(old, curIdx);
			}
			else if (c2 == 80)
			{
				int old = curIdx;
				curIdx = (curIdx + 1) % mItems.size();
				hlMBtn(old, curIdx);
			}
		}
		else if (c == 13)
		{
			switch (curIdx)
			{
			case 0:
				showAdd();
				break;
			case 1:
				showList();
				break;
			case 2:
				showSort();
				break;
			case 3:
				showSearch();
				break;
			case 4:
				showStats();
				break;
			case 5:
				running = false;
				continue;
			default:
				break;
			}

			recalc();
			clrInner();
			drawTitle("CHUONG TRINH QUAN LY SACH THU VIEN");
			drawMMenu();
			drawGuide(
				"Huong dan: [↑] Len | [↓] Xuong | [Enter]: Xac nhan | [Esc]: Thoat");
		}
		else if (c == 27)
		{
			running = false;
		}
	}

	showCursor(true);
	clrInner();
}
