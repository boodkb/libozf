#ifndef IMAGEPARAMETERS
#define IMAGEPARAMETERS

namespace ozf {

struct image_parameters {
    unsigned tile_size;
    unsigned width;
    unsigned height;
    unsigned depth;
    unsigned bpp;
};
}

#endif // IMAGEPARAMETERS
