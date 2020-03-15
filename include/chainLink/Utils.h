// Copyright (c) 2019 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CHAIN_GRABBER_UTILS_H
#define CHAIN_GRABBER_UTILS_H

#include <vector>
#include <cstdint>
#include "openssl/sha.h"
namespace chain_link {
    template<typename IntegerType>
    IntegerType bitsToInt(IntegerType &result, std::vector<unsigned char> bits, bool little_endian = true) {
        result = 0;
        if (little_endian)
            for (int n = sizeof(result); n >= 0; n--)
                result = (result << 8) + bits[n];
        else
            for (unsigned n = 0; n < sizeof(result); n++)
                result = (result << 8) + bits[n];
        return result;
    }

    template<typename IntegerType>
    std::vector<unsigned char> intToBits(IntegerType type, bool little_endian = true) {
        std::vector<unsigned char> result;
        if (little_endian) {
            // 0xff 0xfe 0xfd
            result.push_back(type);
            for (int n = 0; n < sizeof(type) - 1; n++) {
                type = type >> 8;
                result.push_back(type);
            }
        } else {
            for (int i = sizeof(type) - 1; i > 0; i--) {
                result.push_back(type >> (8 * i));
            }
            result.push_back(type);
        }


        return result;
    }

    std::vector<unsigned char> ShaArray(std::vector<unsigned char> input);
    template<typename ArrayType>
    bool compareArray(ArrayType *sourceArray, int16_t size, ArrayType *rhsArray, int16_t rhsSize) {
        if (size != rhsSize)
            return false;

        for (int i = 0; i < size; i++) {
            if (sourceArray[i] != rhsArray[i])
                return false;
        }
        return true;
    }

    uint64_t getVarInt(std::vector<unsigned char>::iterator &data);
    std::vector<unsigned char> getVarIntBytes(uint64_t data);

}
#endif //CHAIN_GRABBER_UTILS_H
