#include "catch.hpp"
#include "test_utils.h"

#include <details/ozf_stream_impl.h>
#include <exceptions/exception.h>

using namespace ozf::details;

namespace {

void test_tile(ozf_stream_impl* stream, ozf::tile_index index, const std::string& test_tile_filename)
{
    const std::vector<char> expected_tile = read_all<char>(test_tile_filename);
    const std::vector<char> actual_tile = stream->get_tile(index);
    REQUIRE(actual_tile == expected_tile);
}

void test_ozfx3_tile(ozf_stream_impl* stream, int scale_index,
    const ozf::scale& scale, int xtile, int ytile)
{
    const std::string filename = "test_data/tiles/ozfx3/" + std::to_string(scale_index) + "-" + std::to_string(xtile) + "-" + std::to_string(ytile) + ".pix";
    test_tile(stream, scale.index(xtile, ytile), filename);
}

void test_ozf4_32bit_tile(ozf_stream_impl* stream, int scale_index,
    const ozf::scale& scale, int xtile, int ytile)
{
    const std::string filename = "test_data/tiles/ozf4_32bit/" + std::to_string(scale_index) + "-" + std::to_string(xtile) + "-" + std::to_string(ytile) + ".pix";
    test_tile(stream, scale.index(xtile, ytile), filename);
}

void test_palette_ozfx3(const std::vector<uint32_t>& act_pal, int scale)
{
    const std::string filename = "test_data/tiles/ozfx3/" + std::to_string(scale) + ".pal";
    const std::vector<uint32_t> exp_pal = read_all<uint32_t>(filename);
    const bool are_equal = std::equal(act_pal.begin(), act_pal.end(), exp_pal.begin());
    REQUIRE(are_equal);
}

void test_palette_ozf4_32bit(const std::vector<uint32_t>& act_pal, int scale)
{
    const std::string filename = "test_data/tiles/ozf4_32bit/" + std::to_string(scale) + ".pal";
    const std::vector<uint32_t> exp_pal = read_all<uint32_t>(filename);
    const bool are_equal = std::equal(act_pal.begin(), act_pal.end(), exp_pal.begin());
    REQUIRE(are_equal);
}
}

TEST_CASE("Ozfx3", "OzfEncryptedStream")
{
    const std::string test_map("test_data/maps/test.ozfx3");

    ozf_stream_impl stream(test_map);
    const ozf::image_parameters params = stream.get_parameters();
    REQUIRE(params.tile_size == 64);
    REQUIRE(params.depth == 1);
    REQUIRE(params.bpp == 8);
    REQUIRE(params.width == 3914);
    REQUIRE(params.height == 4921);

    const std::vector<ozf::scale> scales = stream.scales();
    REQUIRE(scales.size() == 7);

    {
        const unsigned scale_index = 0;
        const ozf::scale& scale = scales[scale_index];
        REQUIRE(scale.zoom == 1.0f);
        REQUIRE(scale.width == 3914);
        REQUIRE(scale.height == 4921);
        REQUIRE(scale.index.column_count() == 62);
        REQUIRE(scale.index.row_count() == 77);
        test_palette_ozfx3(scale.palette, scale_index);
        test_ozfx3_tile(&stream, scale_index, scale, 22, 56);
        test_ozfx3_tile(&stream, scale_index, scale, 40, 37);
    }

    {
        const unsigned scale_index = 1;
        const ozf::scale& scale = scales[scale_index];
        REQUIRE(scale.zoom == 0.25f);
        REQUIRE(scale.width == 978);
        REQUIRE(scale.height == 1230);
        REQUIRE(scale.index.column_count() == 16);
        REQUIRE(scale.index.row_count() == 20);
        test_palette_ozfx3(scale.palette, scale_index);
        test_ozfx3_tile(&stream, scale_index, scale, 13, 12);
        test_ozfx3_tile(&stream, scale_index, scale, 9, 17);
    }

    {
        const unsigned scale_index = 2;
        const ozf::scale& scale = scales[scale_index];
        REQUIRE(scale.zoom == 0.1f);
        REQUIRE(scale.width == 391);
        REQUIRE(scale.height == 492);
        REQUIRE(scale.index.column_count() == 7);
        REQUIRE(scale.index.row_count() == 8);
    }

    {
        const unsigned scale_index = 3;
        const ozf::scale& scale = scales[scale_index];
        REQUIRE(scale.zoom == 0.05f);
        REQUIRE(scale.width == 196);
        REQUIRE(scale.height == 246);
        REQUIRE(scale.index.column_count() == 4);
        REQUIRE(scale.index.row_count() == 4);
    }

    {
        const unsigned scale_index = 4;
        const ozf::scale& scale = scales[scale_index];
        REQUIRE(scale.zoom == 0.025f);
        REQUIRE(scale.width == 98);
        REQUIRE(scale.height == 123);
        REQUIRE(scale.index.column_count() == 2);
        REQUIRE(scale.index.row_count() == 2);
    }
}

TEST_CASE("Ozf4", "OzfEncryptedStream")
{
    const std::string test_map("test_data/maps/test_32bit.ozf4");

    ozf_stream_impl stream(test_map);
    const ozf::image_parameters params = stream.get_parameters();
    REQUIRE(params.tile_size == 64);
    REQUIRE(params.depth == 1);
    REQUIRE(params.bpp == 8);
    REQUIRE(params.width == 4096);
    REQUIRE(params.height == 4096);

    const std::vector<ozf::scale> scales = stream.scales();
    REQUIRE(scales.size() == 7);

    {
        const unsigned scale_index = 0;
        const ozf::scale& scale = scales[scale_index];
        REQUIRE(scale.zoom == 1.0f);
        REQUIRE(scale.width == 4096);
        REQUIRE(scale.height == 4096);
        REQUIRE(scale.index.column_count() == 65);
        REQUIRE(scale.index.row_count() == 65);
        test_palette_ozf4_32bit(scale.palette, scale_index);
        test_ozf4_32bit_tile(&stream, scale_index, scale, 21, 24);
        test_ozf4_32bit_tile(&stream, scale_index, scale, 45, 34);
    }

    {
        const unsigned scale_index = 1;
        const ozf::scale& scale = scales[scale_index];
        REQUIRE(scale.zoom == 0.25f);
        REQUIRE(scale.width == 1024);
        REQUIRE(scale.height == 1024);
        REQUIRE(scale.index.column_count() == 17);
        REQUIRE(scale.index.row_count() == 17);
        test_palette_ozf4_32bit(scale.palette, scale_index);
        test_ozf4_32bit_tile(&stream, scale_index, scale, 11, 6);
        test_ozf4_32bit_tile(&stream, scale_index, scale, 7, 14);
    }

    {
        const unsigned scale_index = 2;
        const ozf::scale& scale = scales[scale_index];
        REQUIRE(scale.zoom == 0.1f);
        REQUIRE(scale.width == 410);
        REQUIRE(scale.height == 410);
        REQUIRE(scale.index.column_count() == 7);
        REQUIRE(scale.index.row_count() == 7);
    }

    {
        const unsigned scale_index = 3;
        const ozf::scale& scale = scales[scale_index];
        REQUIRE(scale.zoom == 0.05f);
        REQUIRE(scale.width == 205);
        REQUIRE(scale.height == 205);
        REQUIRE(scale.index.column_count() == 4);
        REQUIRE(scale.index.row_count() == 4);
    }

    {
        const unsigned scale_index = 4;
        const ozf::scale& scale = scales[scale_index];
        REQUIRE(scale.zoom == 0.025f);
        REQUIRE(scale.width == 102);
        REQUIRE(scale.height == 102);
        REQUIRE(scale.index.column_count() == 2);
        REQUIRE(scale.index.row_count() == 2);
    }
}
