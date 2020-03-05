// Copyright (c) 2019 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef CHAIN_GRABBER_ADDRESS_H
#define CHAIN_GRABBER_ADDRESS_H

#include <array>
#include <vector>
#include <ostream>

namespace chain_link {
    class Address {
    public:
        friend std::ostream &operator<<(std::ostream &os, const Address &address);

    private:
        uint64_t services;
        int64_t timestamp;
        unsigned char ip[16];
        uint16_t port;
        bool initial_;
    public:
        static Address DeSerialize(std::vector<unsigned char> data,bool initial);
        std::vector<unsigned char> Serialize();
        explicit Address(bool initial);
    };
}
#endif //CHAIN_GRABBER_ADDRESS_H
