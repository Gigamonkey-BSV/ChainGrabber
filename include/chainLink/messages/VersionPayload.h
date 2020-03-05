// Copyright (c) 2019 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CHAIN_GRABBER_VERSIONPAYLOAD_H
#define CHAIN_GRABBER_VERSIONPAYLOAD_H

#include "chainLink/messages/Payload.h"
namespace chain_link::messages {
    class Version : public Payload {
    private:
        int32_t version;
        uint64_t services;
        int64_t timestamp;
        uint8_t ip[16];
        uint16_t port;

    };
}
#endif //CHAIN_GRABBER_VERSIONPAYLOAD_H
