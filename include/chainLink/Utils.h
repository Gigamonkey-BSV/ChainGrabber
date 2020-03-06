// Copyright (c) 2019 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CHAIN_GRABBER_UTILS_H
#define CHAIN_GRABBER_UTILS_H

namespace chain_link {
    template<typename IntegerType>
    IntegerType bitsToInt(IntegerType &result,  std::vector<unsigned char> bits, bool little_endian = true) {
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
    std::vector<unsigned char> intToBits(IntegerType type)
    {
        std::vector<unsigned char> result;
        result.push_back(type);
        for(int n=0;n< sizeof(type)-1;n++) {
            type = type >> 8;
            result.push_back(type);
        }


        return result;
    }

}
#endif //CHAIN_GRABBER_UTILS_H
