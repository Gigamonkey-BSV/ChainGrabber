// Copyright (c) 2019 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CHAIN_GRABBER_MESSAGEHEADER_H
#define CHAIN_GRABBER_MESSAGEHEADER_H

#include <cstdint>
#include <array>
#include <ostream>

namespace chain_link::messages {
    class MessageHeader {
    public:
        friend std::ostream &operator<<(std::ostream &os, const MessageHeader &header) {
            os << "MagicBytes: " << std::hex << header.MagicBytes[1] << header.MagicBytes[0] << header.MagicBytes[2] << " CommandName: " << header.CommandName << " PayloadSize: "
               << header.PayloadSize << " Checksum: " << header.Checksum;
            return os;
        }

    private:
        std::array<uint8_t, 4> MagicBytes;
        char CommandName[12];
        uint32_t PayloadSize;
        char Checksum[4];
    };
}


#endif //CHAIN_GRABBER_MESSAGEHEADER_H
