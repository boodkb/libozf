#include "ozf_stream_impl.h"
#include "exceptions/unsupported_exception.h"
#include "utils/decode.h"
#include "utils/decompress.h"

#include <cassert>

static_assert(__BYTE_ORDER == __LITTLE_ENDIAN,
    "Unsupported platform. It should be little endian");

namespace ozf {
namespace details {

    const int OZF_FIRST_HEADER_SIZE = 0xE;
    const int OZF_SECOND_HEADER_SIZE = 0x28;
    const int previewCount = 2;

    void ozf_stream_impl::read_decoded(char* buf, int size)
    {
        _file.read(buf, size);
        if (_decode_fn)
            _decode_fn(buf, size, _key);
    }

    std::vector<char> ozf_stream_impl::read_decoded(int size)
    {
        std::vector<char> buffer(size);
        _file.read(buffer.data(), size);
        if (_decode_fn)
            _decode_fn(buffer.data(), buffer.size(), _key);
        return buffer;
    }

    template <typename T>
    void ozf_stream_impl::read_decoded(T* var)
    {
        _file.read((char*)var, sizeof(T));
        if (_decode_fn)
            _decode_fn((char*)var, sizeof(T), _key);
    }

    template <typename T>
    T ozf_stream_impl::read_decoded()
    {
        T var;
        _file.read((char*)&var, sizeof(T));
        if (_decode_fn)
            _decode_fn((char*)&var, sizeof(T), _key);
        return var;
    }

    void ozf_stream_impl::decode_tile(std::vector<char>& tile_data)
    {
        if (_use_decode_0) {
            //        qWarning() << "UseDecode_0 flag is set, filename -" << _file.fileName();
            //        decode_0((char*)compressedTile.data(), encryptionDepth, key, decodeType_);
        }

        const int tileDataSize = tile_data.size();
        const uint8_t key = _additional_key_modification ? modify_key(tileDataSize, _key) : _key;
        const int encryptionDepth = std::min(_tile_encryption_depth, tileDataSize);
        _decode_fn((char*)tile_data.data(), encryptionDepth, key);
    }

    ozf_stream_impl::ozf_stream_impl(const std::string& filename)
        : _file(filename, _file.binary | _file.in)
    {
        _file.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        if (!_file.is_open())
            throw exception("Failed to open file");

        _file.seekg(0, std::ios_base::end);
        _file_size = _file.tellg();

        _stream_type = read_stream_type();
        switch (_stream_type) {
        case OZF_STREAM_RAW:
        case OZF_STREAM_PROTECTED:
            break;
        case OZF_STREAM_ENCRYPTED:
            _decode_fn = decode1;
            _key = read_primary_key();
            break;
        case OZF_STREAM_NOT_TILED:
            throw exception("Not tiled format. It is not supported");
        default:
            throw exception("Ozf format version was not recognized");
        }

        read_first_header();

        if (_stream_type == OZF_STREAM_ENCRYPTED) {
            const uint32_t keyBlock = read_keyblock();
            set_stream_parameters(keyBlock);
        }

        read_second_header();
        _file.seekg(4, std::ios_base::cur); // skip delimiter
        read_scales();
    }

    uint8_t ozf_stream_impl::read_primary_key()
    {
        const int OZF_KEY_OFFSET = 0xA2;
        _file.seekg(OZF_KEY_OFFSET);
        uint8_t key;
        _file.read((char*)&key, 1);
        return key;
    }

    std::streamoff ozf_stream_impl::read_keyblock_offset()
    {
        _file.seekg(OZF_FIRST_HEADER_SIZE);
        uint8_t offset;
        _file.read((char*)&offset, 1);
        return _file.tellg() + static_cast<std::streamoff>(offset);
    }

    uint32_t ozf_stream_impl::read_keyblock()
    {
        const std::streamoff keyBlockOffset = read_keyblock_offset();
        _file.seekg(keyBlockOffset);
        return read_decoded<uint32_t>();
    }

    void ozf_stream_impl::set_stream_parameters(uint32_t keyblock)
    {
        switch (keyblock) {
        case 0xF323C556:
            _tile_encryption_depth = 247;
            _decode_fn = decode2;
            _key += 0xB9;
            break;
        case 0x58B7A443:
            _tile_encryption_depth = 247;
            _decode_fn = decode2;
            _key += 0xE + 0x6A;
            break;
        case 0x55C6E161:
            _tile_encryption_depth = 247;
            _decode_fn = decode2;
            _key += 0xE + 0x8A;
            _use_decode_0 = false;
            break;
        case 0x58C2E562:
            _tile_encryption_depth = 247;
            _decode_fn = decode4;
            _key += 0xE + 0x8A;
            _use_decode_0 = false;
            break;
        case 0x84476832:
            _tile_encryption_depth = 247;
            _two_bytes_per_pixel = true;
            _large_image_64bit_mode = true;
            _decode_fn = decode4;
            _key += 0xE + 0x8A;
            _use_decode_0 = false;
            break;
        case 0x78439667:
            _tile_encryption_depth = 247;
            _large_image_64bit_mode = true;
            _decode_fn = decode2;
            _key += 0xE + 0x8A;
            _use_decode_0 = false;
            break;
        case 0x7E4A9268:
            _tile_encryption_depth = 247;
            _large_image_64bit_mode = true;
            _decode_fn = decode4;
            _key += 0xE + 0x8A;
            _use_decode_0 = false;
            break;
        case 0x1338A276:
            _tile_encryption_depth = 247;
            _decode_fn = decode2;
            _additional_key_modification = true;
            _key += 0x16 + 0xA0;
            _use_decode_0 = false;
            break;
        case 0x1F3CA177: //Veski
            _tile_encryption_depth = 247;
            _decode_fn = decode4;
            _additional_key_modification = true;
            _key += 0x16 + 0xA0;
            _use_decode_0 = false;
            break;
        case 0xB4761423:
            _tile_encryption_depth = 247;
            _large_image_64bit_mode = true;
            _decode_fn = decode2;
            _additional_key_modification = true;
            _key += 0x16 + 0xA0;
            _use_decode_0 = false;
            break;
        case 0xBA791B25: // gcc250
            _tile_encryption_depth = 247;
            _large_image_64bit_mode = true;
            _decode_fn = decode4;
            _additional_key_modification = true;
            _key += 0x16 + 0xA0;
            _use_decode_0 = false;
            break;

        case 0x7A431F1: // ozfx3, Ozf2Img 3.00+
            _key += 0x8A;
            _use_decode_0 = false;
            break;
        case 0xE592C118: // ozfx3, MapMerge 1.05+
            _key += 0xA0;
            _use_decode_0 = false;
            break;
        case 0xC208F454: // ozfx3, MapMerge 1.04
            _key += 0xA0;
            _use_decode_0 = true;
            break;
        case 0xF9671483:
            _key += 0xA4;
            break;
        case 0xB214A3C5:
            _key += 0x7E;
            break;
        case 0xE6D4A238:
            _key += 0xC1;
            break;
        case 0x59B7A443:
            _key += 0x6A;
            break;
        case 0xF423C556:
            _key += 0xB9;
            break;
        case 0xD56207A9:
        case 0xD46207A9:
        case 0xA8C24235:
        case 0xA7C24235:
        default:
            throw unsupported_exception("Protected ozfx3 images is not supported");
        }
    }

    std::vector<float> ozf_stream_impl::read_zooms()
    {
        // reading zooms
        uint16_t zoomsCount;
        _file.read((char*)&zoomsCount, sizeof(uint16_t));

        if (!zoomsCount)
            throw exception("Zoom count is zero");

        std::vector<float> zooms(zoomsCount + previewCount);
        for (float& zoom : zooms) {
            _file.read((char*)&zoom, sizeof(float));
            zoom /= 100;
        }

        return zooms;
    }

    void ozf_stream_impl::read_scales()
    {
        const std::vector<float> zooms = read_zooms();
        if (_large_image_64bit_mode)
            read_scale_table<int64_t>(zooms);
        else
            read_scale_table<int32_t>(zooms);
    }

    template <typename OffsetType>
    void ozf_stream_impl::read_scale_table(const std::vector<float>& zooms)
    {
        //reading scales table offset
        {
            std::streamoff offset = sizeof(OffsetType);
            if (_stream_type == OZF_STREAM_PROTECTED)
                offset += 0xA72;

            _file.seekg(-offset, std::ios_base::end);
        }
        const OffsetType scalesTableOffset = read_decoded<OffsetType>();

        //reading scales table
        _file.seekg(scalesTableOffset);

        const int scalesCount = zooms.size();
        std::vector<OffsetType> scalesTable(scalesCount);
        for (int i = 0; i < scalesCount; ++i) {
            scalesTable[i] = read_decoded<OffsetType>();
        }

        //reading scales
        _scales.reserve(scalesCount);
        for (int i = 0; i < scalesCount; ++i) {
            _file.seekg(scalesTable[i]);

            scale_params scale;
            scale.zoom = zooms[i];
            read_decoded(&scale.width);
            read_decoded(&scale.height);
            read_decoded(&scale.xtiles);
            read_decoded(&scale.ytiles);

            scale.palette.resize(256);
            int paletteSize = scale.palette.size() * sizeof(uint32_t);
            assert(paletteSize == 1024);

            read_decoded((char*)scale.palette.data(), paletteSize);
            scale.tiles_table_offset = _file.tellg();
            _scales.push_back(scale);
        }
    }

    std::vector<char> ozf_stream_impl::get_tile(tile_index index)
    {
        const scale_params& scale = _scales[index.scale_index];
        std::vector<char> tile_data = _large_image_64bit_mode
            ? read_tile_data<uint64_t>(scale, index.tile_number)
            : read_tile_data<uint32_t>(scale, index.tile_number);

        if (_stream_type == OZF_STREAM_ENCRYPTED)
            decode_tile(tile_data);

        return decompress(tile_data, _params.tile_size * _params.tile_size);
    }

    template <typename OffsetType>
    std::vector<char> ozf_stream_impl::read_tile_data(const scale_params& scale, unsigned tileIndex)
    {
        _file.seekg(scale.tiles_table_offset + tileIndex * sizeof(OffsetType));

        const OffsetType tileBegin = read_decoded<OffsetType>();
        const OffsetType tileEnd = read_decoded<OffsetType>();
        const uint64_t tileSize = tileEnd - tileBegin;
        _file.seekg(tileBegin);
        std::vector<char> tile_data(tileSize);
        _file.read(tile_data.data(), tileSize);
        return tile_data;
    }

    ozf_stream_impl::stream_type ozf_stream_impl::read_stream_type()
    {
        _file.seekg(0);
        uint16_t streamType;
        _file.read((char*)&streamType, sizeof(uint16_t));
        return static_cast<stream_type>(streamType);
    }

    void ozf_stream_impl::read_first_header()
    {
        _file.seekg(0);
        std::vector<char> buffer = read_decoded(OZF_FIRST_HEADER_SIZE);
        if (_stream_type == OZF_STREAM_PROTECTED)
            unprotect(buffer.data(), buffer.size());

        _params.tile_size = buffer[6];
        if (buffer[8] > char(1))
            throw exception("Invalid file format");
    }

    void ozf_stream_impl::read_second_header()
    {
        std::vector<char> buffer = read_decoded(OZF_SECOND_HEADER_SIZE);
        if (_stream_type == OZF_STREAM_PROTECTED)
            unprotect(buffer.data(), buffer.size());

        char* bufferData = const_cast<char*>(buffer.data());
        _params.width = *reinterpret_cast<uint32_t*>(&bufferData[4]);
        _params.height = *reinterpret_cast<uint32_t*>(&bufferData[8]);
        _params.depth = *reinterpret_cast<uint16_t*>(&bufferData[12]);
        _params.bpp = *reinterpret_cast<uint16_t*>(&bufferData[14]);

        if (_params.bpp != 8)
            throw unsupported_exception("Unsupported bpp");
    }

    std::vector<scale> ozf_stream_impl::scales() const
    {
        std::vector<scale> scales;
        scales.reserve(_scales.size());
        for (std::size_t i = 0; i < _scales.size(); ++i)
            scales.push_back(scale{
                _scales[i].zoom,
                _scales[i].width,
                _scales[i].height,
                _scales[i].palette,
                index{ i, _scales[i].xtiles, _scales[i].ytiles } });
        return scales;
    }

    image_parameters ozf_stream_impl::get_parameters() const noexcept
    {
        return _params;
    }
}
}
