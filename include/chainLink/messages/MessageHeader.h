//
// Created by nekosune on 19/02/2020.
//

#ifndef CHAIN_GRABBER_MESSAGEHEADER_H
#define CHAIN_GRABBER_MESSAGEHEADER_H

#include <cstdint>
#include <array>

class MessageHeader {
private:
    std::array<uint8_t,4> MagicBytes;
    char CommandName[12];
    uint32_t PayloadSize;
    char Checksum[4];
};


#endif //CHAIN_GRABBER_MESSAGEHEADER_H
