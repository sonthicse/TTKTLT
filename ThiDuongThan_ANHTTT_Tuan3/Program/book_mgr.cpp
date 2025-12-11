#include "book_mgr.h"

using namespace std;

BookMgr::BookMgr() : filePath("books.dat") {}

BookMgr &BookMgr::get()
{
	static BookMgr instance;
	return instance;
}

size_t BookMgr::load()
{
	books.clear();
	if (!filesystem::exists(filePath))
		return 0;
	ifstream in(filePath, ios::binary);
	if (!in)
		return 0;

	Book b{};
	while (in.read(reinterpret_cast<char *>(&b), sizeof(Book)))
	{
		books.push_back(b);
	}

	return books.size();
}

bool BookMgr::save(const Book &b)
{
	ofstream out(filePath, ios::binary | ios::app);
	if (!out)
		return false;

	out.write(reinterpret_cast<const char *>(&b), sizeof(Book));
	return static_cast<bool>(out);
}

bool BookMgr::add(const Book &b)
{
	books.push_back(b);
	return save(b);
}

const vector<Book> &BookMgr::getList() const { return books; }

// Hàm so sánh để sắp xếp theo ISBN.
bool BookMgr::cmpByISBN(const Book &a, const Book &b)
{
	string sa = a.getISBN();
	string sb = b.getISBN();
	normStr(sa);
	normStr(sb);
	return sa < sb;
}

// Hàm so sánh để sắp xếp theo tiêu đề (tenSach).
bool BookMgr::cmpByTitle(const Book &a, const Book &b)
{
	string sa = a.getTenSach();
	string sb = b.getTenSach();
	normStr(sa);
	normStr(sb);
	return sa < sb;
}

// Hàm so sánh để sắp xếp theo tác giả (tacGia).
bool BookMgr::cmpByAuthor(const Book &a, const Book &b)
{
	string sa = a.getTacGia();
	string sb = b.getTacGia();
	normStr(sa);
	normStr(sb);
	return sa < sb;
}

// Hàm so sánh để sắp xếp theo ngày (ngayNhap).
bool BookMgr::cmpByDate(const Book &a, const Book &b)
{
	Date da = a.getNgayNhap();
	Date db = b.getNgayNhap();
	if (da.getYear() != db.getYear())
		return da.getYear() < db.getYear();
	if (da.getMonth() != db.getMonth())
		return da.getMonth() < db.getMonth();
	return da.getDay() < db.getDay();
}

// Hàm so sánh để sắp xếp theo giá (giaSach).
bool BookMgr::cmpByPrice(const Book &a, const Book &b)
{
	return a.getGiaSach() < b.getGiaSach();
}

// Hàm so sánh để sắp xếp theo mã thể loại (maTL).
bool BookMgr::cmpByCategory(const Book &a, const Book &b)
{
	string sa = a.getMaTL();
	string sb = b.getMaTL();
	normStr(sa);
	normStr(sb);
	return sa < sb;
}

// Hàm so sánh đa cấp. Ưu tiên thể loại, sau đó đến tiêu đề, rồi đến ngày.
bool BookMgr::cmpByMulti(const Book &a, const Book &b)
{
	// So sánh theo thể loại trước
	string ca = a.getMaTL();
	string cb = b.getMaTL();
	normStr(ca);
	normStr(cb);
	if (ca != cb)
	{
		return ca < cb;
	}
	// Nếu thể loại giống nhau, so sánh theo tiêu đề
	string ta = a.getTenSach();
	string tb = b.getTenSach();
	normStr(ta);
	normStr(tb);
	if (ta != tb)
	{
		return ta < tb;
	}
	// Nếu tiêu đề cũng giống nhau, so sánh theo ngày
	Date da = a.getNgayNhap();
	Date db = b.getNgayNhap();
	if (da.getYear() != db.getYear())
		return da.getYear() < db.getYear();
	if (da.getMonth() != db.getMonth())
		return da.getMonth() < db.getMonth();
	return da.getDay() < db.getDay();
}

// Triển khai sắp xếp chèn (Insertion sort).
void BookMgr::insertionSort(
	std::vector<Book> &arr,
	const std::function<bool(const Book &, const Book &)> &cmp)
{
	int n = static_cast<int>(arr.size());
	for (int i = 1; i < n; ++i)
	{
		Book key = arr[i];
		int j = i - 1;
		// Di chuyển các phần tử lớn hơn key đến vị trí trước vị trí hiện tại của chúng.
		while (j >= 0 && cmp(key, arr[j]))
		{
			arr[j + 1] = arr[j];
			--j;
		}
		arr[j + 1] = key;
	}
}

// Hàm phân hoạch cho quick sort.
int BookMgr::partition(
	std::vector<Book> &arr, int low, int high,
	const std::function<bool(const Book &, const Book &)> &cmp)
{
	Book pivot = arr[high];
	int i = low - 1;
	for (int j = low; j <= high - 1; ++j)
	{
		if (cmp(arr[j], pivot))
		{
			++i;
			std::swap(arr[i], arr[j]);
		}
	}
	std::swap(arr[i + 1], arr[high]);
	return i + 1;
}

// Triển khai Quick sort sử dụng sơ đồ phân hoạch Lomuto.
void BookMgr::quickSort(
	std::vector<Book> &arr, int low, int high,
	const std::function<bool(const Book &, const Book &)> &cmp)
{
	if (low < high)
	{
		int pi = partition(arr, low, high, cmp);
		quickSort(arr, low, pi - 1, cmp);
		quickSort(arr, pi + 1, high, cmp);
	}
}

// Hàm merge được sử dụng bởi merge sort.
void BookMgr::merge(
	std::vector<Book> &arr, int left, int mid, int right,
	const std::function<bool(const Book &, const Book &)> &cmp)
{
	int n1 = mid - left + 1;
	int n2 = right - mid;
	std::vector<Book> L(n1), R(n2);
	for (int i = 0; i < n1; ++i)
		L[i] = arr[left + i];
	for (int j = 0; j < n2; ++j)
		R[j] = arr[mid + 1 + j];
	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2)
	{
		if (cmp(L[i], R[j]))
		{
			arr[k] = L[i];
			++i;
		}
		else
		{
			arr[k] = R[j];
			++j;
		}
		++k;
	}
	while (i < n1)
	{
		arr[k++] = L[i++];
	}
	while (j < n2)
	{
		arr[k++] = R[j++];
	}
}

// Triển khai Merge sort.
void BookMgr::mergeSort(
	std::vector<Book> &arr, int left, int right,
	const std::function<bool(const Book &, const Book &)> &cmp)
{
	if (left < right)
	{
		int mid = left + (right - left) / 2;
		mergeSort(arr, left, mid, cmp);
		mergeSort(arr, mid + 1, right, cmp);
		merge(arr, left, mid, right, cmp);
	}
}

// Hàm Heapify được sử dụng bởi heap sort.
void BookMgr::heapify(
	std::vector<Book> &arr, int n, int i,
	const std::function<bool(const Book &, const Book &)> &cmp)
{
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	// Nếu con trái tồn tại và lớn hơn gốc
	if (l < n && cmp(arr[largest], arr[l]))
	{
		largest = l;
	}
	// Nếu con phải tồn tại và lớn hơn phần tử lớn nhất hiện tại
	if (r < n && cmp(arr[largest], arr[r]))
	{
		largest = r;
	}
	// Nếu phần tử lớn nhất không phải là gốc, hoán đổi và tiếp tục heapify
	if (largest != i)
	{
		std::swap(arr[i], arr[largest]);
		heapify(arr, n, largest, cmp);
	}
}

// Triển khai Heap sort.
void BookMgr::heapSort(
	std::vector<Book> &arr,
	const std::function<bool(const Book &, const Book &)> &cmp)
{
	int n = static_cast<int>(arr.size());
	// Xây dựng max heap
	for (int i = n / 2 - 1; i >= 0; --i)
		heapify(arr, n, i, cmp);
	// Lần lượt trích xuất các phần tử từ heap
	for (int i = n - 1; i >= 0; --i)
	{
		// Di chuyển gốc hiện tại xuống cuối
		std::swap(arr[0], arr[i]);
		// gọi max heapify trên heap đã giảm
		heapify(arr, i, 0, cmp);
	}
}

// Phương thức công khai để sắp xếp danh sách sách nội bộ.
void BookMgr::sortList(SortAlgorithm algo, SortCriteria criteria)
{
	// Đảm bảo vector sách được điền dữ liệu mới nhất
	load();
	// Xác định comparator
	std::function<bool(const Book &, const Book &)> cmp;
	switch (criteria)
	{
	case SortCriteria::ISBN:
		cmp = cmpByISBN;
		break;
	case SortCriteria::Title:
		cmp = cmpByTitle;
		break;
	case SortCriteria::Author:
		cmp = cmpByAuthor;
		break;
	case SortCriteria::Date:
		cmp = cmpByDate;
		break;
	case SortCriteria::Price:
		cmp = cmpByPrice;
		break;
	case SortCriteria::Category:
		cmp = cmpByCategory;
		break;
	case SortCriteria::Multi:
		cmp = cmpByMulti;
		break;
	default:
		cmp = cmpByISBN;
		break;
	}
	if (books.empty())
		return;
	switch (algo)
	{
	case SortAlgorithm::Insertion:
		insertionSort(books, cmp);
		break;
	case SortAlgorithm::Quick:
		quickSort(books, 0, static_cast<int>(books.size()) - 1, cmp);
		break;
	case SortAlgorithm::Merge:
		mergeSort(books, 0, static_cast<int>(books.size()) - 1, cmp);
		break;
	case SortAlgorithm::Heap:
		heapSort(books, cmp);
		break;
	default:
		insertionSort(books, cmp);
		break;
	}
	{
		std::ofstream out(filePath, std::ios::binary | std::ios::trunc);
		if (out)
		{
			for (const auto &b : books)
			{
				out.write(reinterpret_cast<const char *>(&b), sizeof(Book));
			}
		}
	}
}
