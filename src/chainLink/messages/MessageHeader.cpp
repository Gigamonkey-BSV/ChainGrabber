// Copyright (c) 2019 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <tuple>
#include "chainLink/messages/MessageHeader.h"
#include "chainLink/Utils.h"

namespace chain_link::messages {

    std::vector<unsigned char> MessageHeader::Serialize() {
        std::vector<unsigned char> ret;
        std::vector<unsigned char> val;
        for(unsigned char MagicByte : MagicBytes)
            ret.push_back(MagicByte);

        for(char i : CommandName)
            ret.push_back(i);
        val=intToBits<uint32_t>(PayloadSize);
        ret.insert(ret.end(),val.begin(),val.end());
        for(unsigned char i:Checksum)
            ret.push_back(i);

        return ret;
    }

    MessageHeader MessageHeader::Deserialize(std::vector<unsigned char>::iterator &data) {
        MessageHeader header{};
        for(unsigned char & MagicByte : header.MagicBytes) {
            MagicByte=*data++;
        }

        for(char & i : header.CommandName) {
            i=*data++;
        }
        bitsToInt<uint32_t>(header.PayloadSize,std::vector(data,data+4));
        data+=4;
        for(unsigned char & i : header.Checksum) {
            i=*data++;
        }
        return header;
    }

    void MessageHeader::setCommand(std::string str) {
        for(int i=0;i<12;i++)
        {
            if(str.length()>i)
                CommandName[i]=str[i];
            else
                CommandName[i]=0x00;
        }

    }

    bool MessageHeader::operator==(const MessageHeader &rhs) const {
        bool equal=true;
        equal&= compareArray<const unsigned char>(MagicBytes.data(),MagicBytes.size(),rhs.MagicBytes.data(),rhs.MagicBytes.size());
        equal&=compareArray<const char>(CommandName,12,rhs.CommandName,12);
        equal&=PayloadSize == rhs.PayloadSize;
        equal&=compareArray<const unsigned char>(Checksum.data(),4,rhs.Checksum.data(),4);

        return equal;
    }

    bool MessageHeader::operator!=(const MessageHeader &rhs) const {
        return !(rhs == *this);
    }

}