#ifndef TILE_INDEX_H
#define TILE_INDEX_H

#include <cstddef>
#include <tuple>

namespace ozf {

namespace details {
    class ozf_stream_impl;
}

class tile_index {
    std::size_t scale_index;
    std::size_t tile_number;

    friend class index;
    friend class details::ozf_stream_impl;
    tile_index(std::size_t scale_index, std::size_t tile_number)
        : scale_index(scale_index)
        , tile_number(tile_number)
    {
    }

public:
    bool operator<(const tile_index& other) const noexcept
    {
        return std::tie(scale_index, tile_number)
            < std::tie(other.scale_index, other.tile_number);
    }
};
}

#endif // TILE_INDEX_H
