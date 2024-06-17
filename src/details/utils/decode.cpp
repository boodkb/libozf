#include "decode.h"

namespace ozf {
namespace details {

    static const uint8_t protectKey[] = {
        0x2D, 0x4A, 0x43, 0xF1, 0x27, 0x9B, 0x69, 0x4F,
        0x36, 0x52, 0x87, 0xEC, 0x5F
    };

    static const uint8_t decodeKey[] = {
        0x2D, 0x4A, 0x43, 0xF1, 0x27, 0x9B, 0x69, 0x4F,
        0x36, 0x52, 0x87, 0xEC, 0x5F, 0x42, 0x53, 0x22,
        0x9E, 0x8B, 0x2D, 0x83, 0x3D, 0xD2, 0x84, 0xBA,
        0xD8, 0x5B //, 0x8B, 0xC0
    };

    void decode1(char* buf, int encryptionDepth, uint8_t initialKey)
    {
        for (int i = 0; i < encryptionDepth; i++) {
            uint8_t temp = decodeKey[i % sizeof(decodeKey)];
            temp += initialKey;
            buf[i] ^= temp;
        }
    }

    //sub_5E8614
    void decode2(char* buf, int encryptionDepth, uint8_t initialKey)
    {
        uint32_t key = initialKey + 0x2E0;
        for (int i = 0; i < encryptionDepth; i++) {
            uint8_t temp = buf[i];
            buf[i] ^= key >> 8;
            key = (temp + key) * 0x3222 + 0x83D2;
        }
    }

    //sub_5E87BC
    void decode4(char* buf, int encryptionDepth, uint8_t initialKey)
    {
        uint32_t key = initialKey + 0x2B6;
        for (int i = 0; i < encryptionDepth; ++i) {
            uint8_t temp = buf[i];
            buf[i] ^= key >> 8;
            key = (temp + key) * 0x336A + 0x80C9;
        }
    }

    void unprotect(char* buf, int encryptionDepth)
    {
        for (long i = 0; i < encryptionDepth; i++) {
            int key_index = i % sizeof(protectKey);
            buf[i] ^= protectKey[key_index];
        }
    }

    uint8_t modify_key(int tileDataSize, uint8_t key)
    {
        uint32_t ts = tileDataSize & 0xFF;
        return 5 * ts * ts + key;
    }
}
}
