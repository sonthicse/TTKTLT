#ifndef BOOK_H
#define BOOK_H

#include "date.h"
#include <cstring>
#include <string>

#pragma pack(push, 1)

class Book
{
private:
	char maTL[20];
	char ISBN[20];
	char tenSach[100];
	char tacGia[100];
	Date ngayNhap;
	int giaSach;

public:
	Book() : maTL{0}, ISBN{0}, tenSach{0}, tacGia{0}, ngayNhap(), giaSach(0) {}
	void setMaTL(const std::string &s)
	{
		strncpy(maTL, s.c_str(), sizeof(maTL) - 1);
		maTL[sizeof(maTL) - 1] = '\0';
	}
	void setISBN(const std::string &s)
	{
		strncpy(ISBN, s.c_str(), sizeof(ISBN) - 1);
		ISBN[sizeof(ISBN) - 1] = '\0';
	}
	void setTenSach(const std::string &s)
	{
		strncpy(tenSach, s.c_str(), sizeof(tenSach) - 1);
		tenSach[sizeof(tenSach) - 1] = '\0';
	}
	void setTacGia(const std::string &s)
	{
		strncpy(tacGia, s.c_str(), sizeof(tacGia) - 1);
		tacGia[sizeof(tacGia) - 1] = '\0';
	}
	void setNgayNhap(const Date &d) { ngayNhap = d; }
	void setGiaSach(int g) { giaSach = g; }
	std::string getMaTL() const { return std::string(maTL); }
	std::string getISBN() const { return std::string(ISBN); }
	std::string getTenSach() const { return std::string(tenSach); }
	std::string getTacGia() const { return std::string(tacGia); }
	Date getNgayNhap() const { return ngayNhap; }
	int getGiaSach() const { return giaSach; }
};

#pragma pack(pop)

#endif
