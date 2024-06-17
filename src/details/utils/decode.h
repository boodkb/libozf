#ifndef OZFUTILS_H
#define OZFUTILS_H

#include <cstdint>

namespace ozf {
namespace details {

    void decode1(char* buf, int encryptionDepth, uint8_t initialKey);
    void decode2(char* buf, int encryptionDepth, uint8_t initialKey);
    void decode4(char* buf, int encryptionDepth, uint8_t initialKey);

    void unprotect(char* buf, int encryptionDepth);

    uint8_t modify_key(int tileDataSize, uint8_t key);
}
}

#endif // OZFUTILS_H
