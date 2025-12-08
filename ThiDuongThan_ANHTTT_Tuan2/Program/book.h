#ifndef BOOK_H
#define BOOK_H

#include "date.h"
#include <cstring>
#include <string>

using namespace std;

#pragma pack(push, 1)

class Book {
private:
    char maTL[20];
    char ISBN[20];
    char tenSach[100];
    char tacGia[100];
    Date ngayNhap;
    int giaSach;
public:
    Book() : maTL{0}, ISBN{0}, tenSach{0}, tacGia{0}, ngayNhap(), giaSach(0) {}
    void setMaTL(const string &s) {
        strncpy(maTL, s.c_str(), sizeof(maTL) - 1);
        maTL[sizeof(maTL) - 1] = '\0';
    }
    void setISBN(const string &s) {
        strncpy(ISBN, s.c_str(), sizeof(ISBN) - 1);
        ISBN[sizeof(ISBN) - 1] = '\0';
    }
    void setTenSach(const string &s) {
        strncpy(tenSach, s.c_str(), sizeof(tenSach) - 1);
        tenSach[sizeof(tenSach) - 1] = '\0';
    }
    void setTacGia(const string &s) {
        strncpy(tacGia, s.c_str(), sizeof(tacGia) - 1);
        tacGia[sizeof(tacGia) - 1] = '\0';
    }
    void setNgayNhap(const Date &d) { ngayNhap = d; }
    void setGiaSach(int g) { giaSach = g; }
    string getMaTL() const { return string(maTL); }
    string getISBN() const { return string(ISBN); }
    string getTenSach() const { return string(tenSach); }
    string getTacGia() const { return string(tacGia); }
    Date getNgayNhap() const { return ngayNhap; }
    int getGiaSach() const { return giaSach; }
};

#pragma pack(pop)

#endif
