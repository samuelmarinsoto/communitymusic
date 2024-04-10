#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <tuple>
#include "MP3Tags.hpp"

// C++ implementation of limited size array allocated between virtual and physical memory
class PagedArray {
private:
	size_t size, objsize, rampages, pagesize, pagecount, objs_per_page, previndex;
	char* filename;
	std::vector<std::tuple<size_t, std::vector<MP3Tags>>> active_pages;
	std::fstream file;
    size_t currentPage_ = static_cast<size_t>(-1); // Invalid page index

    void loadPage(size_t pageIndex);
    void savePage(std::tuple<size_t, std::vector<MP3Tags>>& savetuple);
    void push_front(std::tuple<size_t, std::vector<MP3Tags>>& newtuple);
    void switch_front(std::tuple<size_t, std::vector<MP3Tags>>& switchtuple, int switchindex);  	

public:
    PagedArray(size_t size_, size_t objsize_, size_t rampages_, size_t pagesize_, char* filename_);
    ~PagedArray();
    MP3Tags& operator[](size_t index);
    size_t getSize();
};
