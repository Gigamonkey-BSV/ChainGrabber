// Copyright (c) 2020 Katrina Swales
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CHAIN_GRABBER_WHATSONCHAINAPI_H
#define CHAIN_GRABBER_WHATSONCHAINAPI_H

#include "BitcoinAPI.h"

namespace chain_grabber {
    class WhatsOnChainAPI : public BitcoinAPI {
    public:
        header GetBlockHeader(std::string hash) override;

        std::string GetHeadBlockHash() override;

    };
}
#endif //CHAIN_GRABBER_WHATSONCHAINAPI_H
