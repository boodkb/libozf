#include "test_utils.h"

#include <iomanip>
#include <iterator>
#include <sstream>

std::vector<char> from_hex(const std::string& str)
{
    size_t len = str.length();
    std::vector<char> out;
    for (size_t i = 0; i < len; i += 2) {
        std::istringstream stream(str.substr(i, 2));
        int x;
        stream >> std::hex >> x;
        out.push_back(x);
    }
    return out;
}
