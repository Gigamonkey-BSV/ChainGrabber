// Copyright (c) 2019 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include "chainLink/Utils.h"
namespace chain_link {

    uint64_t getVarInt(std::vector<unsigned char>::iterator &data) {
        unsigned char indicator = *data++;
        uint64_t result = indicator;
        if (indicator < 0xFD)
            result = indicator;
        if (indicator == 0xFD) {
            bitsToInt<uint16_t>(reinterpret_cast<unsigned short &>(result), std::vector<unsigned char>(data, data + 2));
            data += 2;
        }
        if (indicator == 0xFE) {
            bitsToInt<uint32_t>(reinterpret_cast<unsigned int &>(result), std::vector<unsigned char>(data, data + 4));
            data += 4;
        }
        if (indicator == 0xFF) {
            bitsToInt<uint64_t>(result, std::vector<unsigned char>(data, data + 8));
            data += 8;
        }
        return result;
    }

    std::vector<unsigned char> getVarIntBytes(uint64_t data) {
        std::vector<unsigned char> ret;
        std::vector<unsigned char> val;
        if(data < 0xFD)
            ret.push_back(data);
        else if(data<=0xFFFF)
        {
            ret.push_back(0xFD);
            val=intToBits<uint16_t>(data);
        }
        else if(data <=0xFFFFFFFF) {
            ret.push_back(0xFE);
            val=intToBits<uint32_t>(data);
        } else
        {
            ret.push_back(0xFF);
            val=intToBits<uint64_t>(data);
        }
        return ret;
    }

    std::vector<unsigned char> ShaArray(std::vector<unsigned char> input) {
        std::vector<unsigned  char> output;
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256,input.data(),input.size());
        SHA256_Final(hash,&sha256);

        for(unsigned char chr:hash)
            output.push_back(chr);
        return output;
    }
}