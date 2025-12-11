#ifndef BOOK_MGR_H
#define BOOK_MGR_H

#include "book.h"
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>

using namespace std;

class BookMgr {
private:
    vector<Book> books;
    string filePath;
    BookMgr();
    BookMgr(const BookMgr&) = delete;
    BookMgr& operator=(const BookMgr&) = delete;
public:
    static BookMgr& get();
    size_t load();
    bool save(const Book &b);
    bool add(const Book &b);
    const vector<Book>& getList() const;
};

#endif
