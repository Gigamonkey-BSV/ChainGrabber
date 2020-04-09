// Copyright (c) 2019 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/asio.hpp>

#ifndef CHAIN_GRABBER_PAYLOAD_H
#define CHAIN_GRABBER_PAYLOAD_H


namespace chain_link::messages {
    class Payload {
    public:
        virtual std::vector<unsigned char> Serialize() =0;
        virtual Payload* Clone()=0;
    };
}
#endif //CHAIN_GRABBER_PAYLOAD_H
