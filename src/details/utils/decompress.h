#ifndef DECOMPRESSOR_H
#define DECOMPRESSOR_H

#include <cstdint>
#include <vector>

namespace ozf {
namespace details {
    std::vector<char> decompress(const std::vector<char>& data, uint32_t output_size);
}
}

#endif // DECOMPRESSOR_H
