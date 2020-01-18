// Copyright (c) 2019 Katrina Swales
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CHAIN_GRABBER_BITCOINHEADER_H
#define CHAIN_GRABBER_BITCOINHEADER_H

#include <stdint-gcc.h>
#include <string>
namespace chain_grabber {
    struct header {
        int32_t Height;
        int32_t Version;
        std::string Previous;
        std::string Hash;
        std::string MerkleRoot;
        int64_t Timestamp;
        std::string Target;
        std::string Nonce;
    };
}
#endif //CHAIN_GRABBER_BITCOINHEADER_H
