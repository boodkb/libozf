#include "ozf_stream.h"
#include "details/ozf_stream_impl.h"

namespace ozf {

ozf_stream::ozf_stream(const std::string& filename)
    : _impl(new details::ozf_stream_impl(filename))
{
}

std::vector<scale> ozf_stream::scales() const
{
    return _impl->scales();
}

std::vector<char> ozf_stream::get_tile(tile_index index) const
{
    return _impl->get_tile(index);
}

image_parameters ozf_stream::parameters() const noexcept
{
    return _impl->get_parameters();
}
}
