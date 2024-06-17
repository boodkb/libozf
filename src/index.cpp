#include "index.h"
#include "exceptions/exception.h"

namespace ozf {

tile_index index::operator()(unsigned column, unsigned row) const
{
    if (column < _columns && row < _rows) {
        const unsigned tile_number = row * _columns + column;
        return tile_index{ _scale_index, tile_number };
    }

    throw exception("Invalid tile index");
}
}
