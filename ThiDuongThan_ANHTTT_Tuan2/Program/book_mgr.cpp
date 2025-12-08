#include "book_mgr.h"

using namespace std;

BookMgr::BookMgr() : filePath("books.dat") {}

BookMgr &BookMgr::get() {
    static BookMgr instance;
    return instance;
}

size_t BookMgr::load() {
    books.clear();
    if (!filesystem::exists(filePath)) return 0;
    ifstream in(filePath, ios::binary);
    if (!in) return 0;

    Book b{};
    while (in.read(reinterpret_cast<char*>(&b), sizeof(Book))) {
        books.push_back(b);
    }

    return books.size();
}

bool BookMgr::save(const Book &b) {
    ofstream out(filePath, ios::binary | ios::app);
    if (!out) return false;

    out.write(reinterpret_cast<const char*>(&b), sizeof(Book));
    return static_cast<bool>(out);
}

bool BookMgr::add(const Book &b) {
    books.push_back(b);
    return save(b);
}

const vector<Book>& BookMgr::getList() const {
    return books;
}
