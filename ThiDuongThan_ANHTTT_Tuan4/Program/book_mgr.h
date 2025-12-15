#ifndef BOOK_MGR_H
#define BOOK_MGR_H

#include "utils.h"
#include "book.h"
#include <filesystem>
#include <fstream>
#include <functional>
#include <string>
#include <vector>

using namespace std;

class BookMgr
{
private:
	vector<Book> books;
	string filePath;
	BookMgr();
	BookMgr(const BookMgr &) = delete;
	BookMgr &operator=(const BookMgr &) = delete;
	// Các hàm so sánh để sắp xếp.
	static bool cmpByISBN(const Book &a, const Book &b);
	static bool cmpByTitle(const Book &a, const Book &b);
	static bool cmpByAuthor(const Book &a, const Book &b);
	static bool cmpByDate(const Book &a, const Book &b);
	static bool cmpByPrice(const Book &a, const Book &b);
	static bool cmpByCategory(const Book &a, const Book &b);
	static bool cmpByMulti(const Book &a, const Book &b);

	// Triển khai các thuật toán sắp xếp.
	static void insertionSort(std::vector<Book> &arr, const std::function<bool(const Book &, const Book &)> &cmp);
	static void quickSort(std::vector<Book> &arr, int low, int high, const std::function<bool(const Book &, const Book &)> &cmp);
	static int partition(std::vector<Book> &arr, int low, int high, const std::function<bool(const Book &, const Book &)> &cmp);
	static void mergeSort(std::vector<Book> &arr, int left, int right, const std::function<bool(const Book &, const Book &)> &cmp);
	static void merge(std::vector<Book> &arr, int left, int mid, int right, const std::function<bool(const Book &, const Book &)> &cmp);
	static void heapSort(std::vector<Book> &arr, const std::function<bool(const Book &, const Book &)> &cmp);
	static void heapify(std::vector<Book> &arr, int n, int i, const std::function<bool(const Book &, const Book &)> &cmp);

public:
	static BookMgr &get();
	size_t load();
	bool save(const Book &b);
	bool add(const Book &b);
	const vector<Book> &getList() const;

	// Liệt kê các thuật toán sắp xếp được hỗ trợ
	enum class SortAlgorithm
	{
		Insertion = 0,
		Quick,
		Merge,
		Heap
	};

	// Liệt kê các tiêu chí sắp xếp được hỗ trợ
	enum class SortCriteria
	{
		ISBN = 0,
		Title,
		Author,
		Date,
		Price,
		Category,
		Multi
	};

	// Sắp xếp danh sách sách nội bộ bằng cách sử dụng thuật toán và tiêu chí so sánh được chỉ định.
	void sortList(SortAlgorithm algo, SortCriteria criteria);
};

#endif
