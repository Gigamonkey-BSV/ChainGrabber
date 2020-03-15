// Copyright (c) 2019 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CHAIN_GRABBER_MESSAGEHEADER_H
#define CHAIN_GRABBER_MESSAGEHEADER_H

#include <cstdint>
#include <array>
#include <ostream>
#include <vector>

namespace chain_link::messages {
    class MessageHeader {
    public:
        friend std::ostream &operator<<(std::ostream &os, const MessageHeader &header) {
            os << "MagicBytes: ";
            for(unsigned char i: header.MagicBytes) {
                os << std::hex << (unsigned int) i << ", ";
            }
            os << " CommandName: " << header.CommandName << " PayloadSize: "
               << header.PayloadSize << " Checksum: " ;
            for(unsigned char i:header.Checksum)
                os << std::hex << (unsigned int) i << ", ";
            return os;
        }
        std::vector<unsigned char> Serialize();
        static MessageHeader Deserialize(std::vector<unsigned char>::iterator& data);
    public:
        std::array<unsigned char, 4> MagicBytes;
        char CommandName[12];
        uint32_t PayloadSize;
        std::array<unsigned char,4> Checksum;
        void setCommand(std::string str);

        bool operator==(const MessageHeader &rhs) const;

        bool operator!=(const MessageHeader &rhs) const;
    };
}


#endif //CHAIN_GRABBER_MESSAGEHEADER_H
