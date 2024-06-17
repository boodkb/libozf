#include "decompress.h"
#include "exceptions/exception.h"

#include <zlib.h>

namespace ozf {
namespace details {

    std::vector<char> decompress(const std::vector<char>& data, uint32_t output_size)
    {
        z_stream stream;
        stream.zalloc = (alloc_func)0;
        stream.zfree = (free_func)0;

        int result = inflateInit(&stream);
        if (result != Z_OK) {
            throw exception("inflateInit(...) failed");
        }

        std::vector<char> output(output_size);
        stream.avail_in = data.size();
        stream.next_in = (Bytef*)data.data();

        stream.avail_out = output_size;
        stream.next_out = (Bytef*)output.data();
        result = inflate(&stream, Z_NO_FLUSH);
        if (stream.avail_out != 0 || result != Z_STREAM_END) {
            inflateEnd(&stream);
            throw exception("inflate(...) failed");
        }

        inflateEnd(&stream);
        return output;
    }
}
}
