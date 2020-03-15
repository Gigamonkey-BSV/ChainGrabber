// Copyright (c) 2019 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CHAIN_GRABBER_BASEMESSAGE_H
#define CHAIN_GRABBER_BASEMESSAGE_H

#include <cstdint>
#include <array>
#include "MessageHeader.h"
#include "Payload.h"
#include <boost/container_hash/hash.hpp>

namespace chain_link::messages {
        class BaseMessage {
        public:
            MessageHeader header;
            Payload* payload;
            bool isValid();
            static BaseMessage MakeMessage(std::string messageType,Payload& payload);
        };


}
#endif //CHAIN_GRABBER_BASEMESSAGE_H
