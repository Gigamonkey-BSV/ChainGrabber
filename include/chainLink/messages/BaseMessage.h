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
            std::shared_ptr<Payload> payload;
            bool isValid();
            static BaseMessage MakeMessage(std::string messageType,std::shared_ptr<chain_link::messages::Payload> payload);
            void setPayload(std::shared_ptr<chain_link::messages::Payload> payload1);
            BaseMessage();
            std::vector<unsigned char> Serialize();
        };


}
#endif //CHAIN_GRABBER_BASEMESSAGE_H
