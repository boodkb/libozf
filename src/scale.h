#ifndef SCALE
#define SCALE

#include "index.h"

#include <cstdint>
#include <vector>

namespace ozf {

struct scale {
    float zoom;
    unsigned width;
    unsigned height;
    std::vector<uint32_t> palette;
    ozf::index index;
};
}

#endif // SCALE
