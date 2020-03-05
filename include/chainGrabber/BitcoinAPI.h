// Copyright (c) 2019 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CHAIN_GRABBER_BITCOINAPI_H
#define CHAIN_GRABBER_BITCOINAPI_H

#include "BitcoinHeader.h"

namespace chain_grabber {
    class BitcoinAPI {
    public:
        virtual header GetBlockHeader(std::string hash) =0;
        virtual std::string GetHeadBlockHash() =0;
    };
}
#endif //CHAIN_GRABBER_BITCOINAPI_H
