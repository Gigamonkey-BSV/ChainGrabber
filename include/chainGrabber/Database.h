// Copyright (c) 2019 Katrina Swales
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CHAIN_GRABBER_DATABASE_H
#define CHAIN_GRABBER_DATABASE_H

#include "chainGrabber/BitcoinHeader.h"
#include <string>
namespace chain_grabber {
    class Database {
    public:
        virtual void connect() =0;
        virtual std::string InsertHeader(header header) =0;
        virtual header GetHeader(std::string id) =0;
        virtual header FindHeaderByMerkle(std::string hash) =0;
        virtual header FindHeaderByHash(std::string hash) =0;
    };
}
#endif //CHAIN_GRABBER_DATABASE_H
