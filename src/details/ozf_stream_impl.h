#ifndef OZFSTREAMIMPL_H
#define OZFSTREAMIMPL_H

#include "image_parameters.h"
#include "scale.h"

#include <fstream>
#include <functional>
#include <vector>

namespace ozf {
namespace details {

    class ozf_stream_impl {
    public:
        explicit ozf_stream_impl(const std::string& filename);
        virtual ~ozf_stream_impl() {}

        image_parameters get_parameters() const noexcept;
        std::vector<scale> scales() const;
        std::vector<char> get_tile(tile_index index);

    private:
        struct scale_params {
            float zoom;
            uint32_t width;
            uint32_t height;
            uint16_t xtiles;
            uint16_t ytiles;
            std::vector<uint32_t> palette;
            uint32_t tiles_table_offset;
        };

        enum stream_type {
            OZF_STREAM_NOT_TILED = 0x7777,
            OZF_STREAM_RAW = 0x7778,
            OZF_STREAM_PROTECTED = 0x7779,
            OZF_STREAM_ENCRYPTED = 0x7780
        };

        using decode_func = std::function<void(char*, int, uint8_t)>;
        decode_func _decode_fn;

        void read_decoded(char* buf, int size);
        std::vector<char> read_decoded(int size);

        template <typename T>
        void read_decoded(T* var);

        template <typename T>
        T read_decoded();

        void decode_tile(std::vector<char>& tile_data);

        std::vector<float> read_zooms();
        void read_scales();

        stream_type read_stream_type();
        void read_first_header();
        void read_second_header();

        uint8_t read_primary_key();
        std::streamoff read_keyblock_offset();
        uint32_t read_keyblock();

        void set_stream_parameters(uint32_t keyblock);

        template <typename OffsetType>
        void read_scale_table(const std::vector<float>& zooms);

        template <typename OffsetType>
        std::vector<char> read_tile_data(const scale_params& scale, unsigned tileIndex);

        std::ifstream _file;
        std::size_t _file_size;
        stream_type _stream_type;
        uint8_t _key = 0;
        bool _large_image_64bit_mode = false;
        bool _two_bytes_per_pixel = false;
        bool _additional_key_modification = false;
        bool _use_decode_0 = false;
        int _tile_encryption_depth = 16;

        std::vector<scale_params> _scales;
        image_parameters _params;
    };
}
}

#endif // OZFSTREAMIMPL_H
