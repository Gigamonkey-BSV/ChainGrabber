//
// Created by nekosune on 04/02/2020.
//

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
