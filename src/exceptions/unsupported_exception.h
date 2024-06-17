#ifndef UNSUPPORTEDEXCEPTION
#define UNSUPPORTEDEXCEPTION

#include "exception.h"

namespace ozf {

struct unsupported_exception : public exception {
    using exception::exception;
};
}

#endif // UNSUPPORTEDEXCEPTION
