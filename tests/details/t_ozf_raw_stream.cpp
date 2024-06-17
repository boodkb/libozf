#include "catch.hpp"
#include "test_utils.h"

#include <algorithm>
#include <details/ozf_stream_impl.h>
#include <exceptions/exception.h>

using namespace ozf::details;

namespace {

void test_tile(ozf_stream_impl* stream, int scale_index, const ozf::scale& scale, int xtile, int ytile)
{
    const std::string filename = "test_data/tiles/ozf2/" + std::to_string(scale_index) + "-" + std::to_string(xtile) + "-" + std::to_string(ytile) + ".pix";
    const std::vector<char> expected_tile = read_all<char>(filename);
    const std::vector<char> actual_tile = stream->get_tile(scale.index(xtile, ytile));
    REQUIRE(actual_tile == expected_tile);
}

void test_palette(const std::vector<uint32_t>& act_pal, int scale)
{
    const std::string filename = "test_data/tiles/ozf2/" + std::to_string(scale) + ".pal";
    const std::vector<uint32_t> exp_pal = read_all<uint32_t>(filename);
    const bool are_equal = std::equal(act_pal.begin(), act_pal.end(), exp_pal.begin());
    REQUIRE(are_equal);
}
}

TEST_CASE("Ozf2", "OzfRawStream")
{
    const std::string test_map("test_data/maps/test.ozf2");

    ozf_stream_impl stream(test_map);
    const ozf::image_parameters params = stream.get_parameters();
    REQUIRE(params.tile_size == 64);
    REQUIRE(params.depth == 1);
    REQUIRE(params.bpp == 8);
    REQUIRE(params.width == 3813);
    REQUIRE(params.height == 5230);

    const std::vector<ozf::scale> scales = stream.scales();
    REQUIRE(scales.size() == 7);

    {
        const unsigned scale_index = 0;
        const ozf::scale& scale = scales[scale_index];
        REQUIRE(scale.zoom == 1.0f);
        REQUIRE(scale.width == 3813);
        REQUIRE(scale.height == 5230);
        REQUIRE(scale.index.column_count() == 60);
        REQUIRE(scale.index.row_count() == 82);
        test_palette(scale.palette, scale_index);
        test_tile(&stream, 0, scale, 19, 67);
        test_tile(&stream, 0, scale, 47, 38);
        test_tile(&stream, 0, scale, 56, 44);
    }

    {
        const unsigned scale_index = 1;
        const ozf::scale& scale = scales[scale_index];
        REQUIRE(scale.zoom == 0.25f);
        REQUIRE(scale.width == 953);
        REQUIRE(scale.height == 1308);
        REQUIRE(scale.index.column_count() == 15);
        REQUIRE(scale.index.row_count() == 21);
        test_palette(scale.palette, scale_index);
        test_tile(&stream, 1, scale, 14, 19);
        test_tile(&stream, 1, scale, 5, 9);
    }

    {
        const ozf::scale& scale = scales[2];
        REQUIRE(scale.zoom == 0.1f);
        REQUIRE(scale.width == 381);
        REQUIRE(scale.height == 523);
        REQUIRE(scale.index.column_count() == 6);
        REQUIRE(scale.index.row_count() == 9);
    }

    {
        const ozf::scale& scale = scales[3];
        REQUIRE(scale.zoom == 0.05f);
        REQUIRE(scale.width == 191);
        REQUIRE(scale.height == 262);
        REQUIRE(scale.index.column_count() == 3);
        REQUIRE(scale.index.row_count() == 5);
    }

    {
        const ozf::scale& scale = scales[4];
        REQUIRE(scale.zoom == 0.025f);
        REQUIRE(scale.width == 95);
        REQUIRE(scale.height == 131);
        REQUIRE(scale.index.column_count() == 2);
        REQUIRE(scale.index.row_count() == 3);
    }
}
