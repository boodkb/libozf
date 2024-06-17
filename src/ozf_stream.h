#ifndef OZFSTREAM_H
#define OZFSTREAM_H

#include "image_parameters.h"
#include "scale.h"
#include "tile_index.h"

#include <memory>
#include <vector>

namespace ozf {

namespace details {
    class ozf_stream_impl;
}

class ozf_stream final {
public:
    explicit ozf_stream(const std::string& filename);
    ~ozf_stream() = default;
    std::vector<scale> scales() const;
    std::vector<char> get_tile(tile_index index) const;
    image_parameters parameters() const noexcept;

private:
    std::unique_ptr<details::ozf_stream_impl> _impl;
};
}

#endif // OZFSTREAM_H
