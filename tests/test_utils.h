#ifndef TEST_UTILS_H
#define TEST_UTILS_H
#include "catch.hpp"

#include <fstream>
#include <string>
#include <vector>

std::vector<char> from_hex(const std::string& str);

template <typename T>
std::vector<T> read_all(const std::string& filename)
{
    std::ifstream fs(filename, std::fstream::binary | std::fstream::ate);
    if (!fs.is_open())
        FAIL("Test file was not found: " + filename);

    auto size = fs.tellg();
    if (size % sizeof(T) != 0)
        FAIL("Invalid test file: " + filename);

    std::vector<T> content(size / sizeof(T));
    fs.seekg(0);
    fs.read((char*)content.data(), size);
    return content;
}

#endif // TEST_UTILS_H
