#ifndef OZF_EXCEPTION
#define OZF_EXCEPTION

#include <stdexcept>

namespace ozf {

struct exception : public std::logic_error {
    using std::logic_error::logic_error;
};
}

#endif // OZF_EXCEPTION
