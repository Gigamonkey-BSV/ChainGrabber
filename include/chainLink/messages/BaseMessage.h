//
// Created by nekosune on 19/02/2020.
//

#ifndef CHAIN_GRABBER_BASEMESSAGE_H
#define CHAIN_GRABBER_BASEMESSAGE_H

#include <cstdint>
#include <array>

namespace chain_link::messages {
        class BaseMessage {
        private:
            std::array<uint8_t,4> MagicBytes;

        };
    }
#endif //CHAIN_GRABBER_BASEMESSAGE_H
