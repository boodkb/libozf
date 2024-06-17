#ifndef INDEX_H
#define INDEX_H

#include "tile_index.h"

#include <cstddef>

namespace ozf {

class index {
public:
    tile_index operator()(unsigned column, unsigned row) const;

    unsigned column_count() const noexcept
    {
        return _columns;
    }

    unsigned row_count() const noexcept
    {
        return _rows;
    }

private:
    index(std::size_t scale_index, unsigned columns, unsigned rows)
        : _scale_index(scale_index)
        , _columns(columns)
        , _rows(rows)
    {
    }

    friend class details::ozf_stream_impl;

    std::size_t _scale_index;
    unsigned _columns;
    unsigned _rows;
};
}

#endif // INDEX_H
