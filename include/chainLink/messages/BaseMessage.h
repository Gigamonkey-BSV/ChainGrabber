// Copyright (c) 2019 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CHAIN_GRABBER_BASEMESSAGE_H
#define CHAIN_GRABBER_BASEMESSAGE_H

#include <cstdint>
#include <array>
#include "MessageHeader.h"
#include "Payload.h"

namespace chain_link::messages {
        class BaseMessage {
        private:
            MessageHeader header;
            Payload payload;
        };
    }
#endif //CHAIN_GRABBER_BASEMESSAGE_H
