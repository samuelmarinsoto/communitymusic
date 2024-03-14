#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

const std::string FILENAME = "paged_array.bin";
const size_t PAGE_SIZE = 4096;  // Adjust as needed

class PagedArray {
public:
    PagedArray(size_t size) : size_(size), page_count_(size / PAGE_SIZE + (size % PAGE_SIZE != 0)), file_(FILENAME, std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc) {
        if (!file_.is_open()) {
            std::cerr << "Error opening file for PagedArray\n";
            std::exit(EXIT_FAILURE);
        }

        // Resize the file to accommodate all pages
        file_.seekp((page_count_ * PAGE_SIZE) - 1);
        file_.put(0);
        file_.seekp(0);
    }

    ~PagedArray() {
        file_.close();
    }

    int& operator[](size_t index) {
        size_t pageIndex = index / PAGE_SIZE;
        size_t pageOffset = index % PAGE_SIZE;

        if (pageIndex >= page_count_) {
            std::cerr << "Index out of bounds\n";
            std::exit(EXIT_FAILURE);
        }

        // Load the page into memory if not already loaded
        if (currentPage_ != pageIndex) {
            loadPage(pageIndex);
            currentPage_ = pageIndex;
        }

        return pages_[pageOffset];
    }

private:
    void loadPage(size_t pageIndex) {
        file_.seekg(pageIndex * PAGE_SIZE);
        file_.read(reinterpret_cast<char*>(pages_.data()), PAGE_SIZE);
    }

    void savePage(size_t pageIndex) {
        file_.seekp(pageIndex * PAGE_SIZE);
        file_.write(reinterpret_cast<const char*>(pages_.data()), PAGE_SIZE);
    }

    size_t size_;
    size_t page_count_;
    std::fstream file_;
    std::vector<int> pages_ = std::vector<int>(PAGE_SIZE / sizeof(int));
    size_t currentPage_ = static_cast<size_t>(-1); // Invalid page index
};

int main() {
    const size_t arraySize = 10000;
    PagedArray pagedArray(arraySize);

    // Usage example
    for (size_t i = 0; i < arraySize; ++i) {
        pagedArray[i] = i * i;
    }

    std::cout << "Element at index 54: " << pagedArray[54] << std::endl;

    return 0;
}
