// Copyright (c) 2020 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainLink/Utils.h>

#include <utility>
#include <chainLink/Constants.h>
#include "chainLink/messages/BaseMessage.h"
#include "chainLink/Utils.h"

namespace chain_link::messages {

    bool BaseMessage::isValid() {
        std::vector<unsigned char> payloadVector=payload->Serialize();
        std::vector<unsigned char> hash=ShaArray(payloadVector);
        hash=ShaArray(hash);
        return compareArray<unsigned char>(header.Checksum.data(),4,hash.data(),4);
    }

    BaseMessage BaseMessage::MakeMessage(std::string messageType, Payload& payload) {
        BaseMessage msg{};
        msg.payload =payload.Clone();
        msg.header.MagicBytes=Config::getConfig().GetMagicBytes();
        msg.header.setCommand(std::move(messageType));
        std::vector<unsigned char> payloadVector = msg.payload->Serialize();
        msg.header.PayloadSize=payloadVector.size();
        std::vector<unsigned char> hash=ShaArray(ShaArray(payloadVector));
        auto itr=hash.begin();
        for(unsigned char& c:msg.header.Checksum)
            c=*itr++;
        return msg;
    }


}
