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
        Payload* payloadDir=payload.get();
        std::vector<unsigned char> payloadVector=payloadDir->Serialize();
        std::vector<unsigned char> hash=ShaArray(payloadVector);
        hash=ShaArray(hash);
        return compareArray<unsigned char>(header.Checksum.data(),4,hash.data(),4);
    }

    BaseMessage BaseMessage::MakeMessage(std::string messageType, std::shared_ptr<chain_link::messages::Payload> payload) {
        BaseMessage msg{};
        msg.setPayload(payload);
        msg.header.MagicBytes=Config::getConfig().GetMagicBytes();
        msg.header.setCommand(std::move(messageType));
        std::vector<unsigned char> hash;
        if(payload!= nullptr) {
            std::vector<unsigned char> payloadVector = msg.payload->Serialize();
            msg.header.PayloadSize = payloadVector.size();

            hash = ShaArray(ShaArray(payloadVector));
        }
        else {
            msg.header.PayloadSize = 0;
            hash.push_back(0xe2);
            hash.push_back(0xe0);
            hash.push_back(0xf6);
            hash.push_back(0x5d);
        }

        auto itr=hash.begin();
        for(unsigned char& c:msg.header.Checksum)
            c=*itr++;
        return msg;
    }

    BaseMessage::BaseMessage() {}



    void BaseMessage::setPayload(std::shared_ptr<chain_link::messages::Payload> payload1) {
        payload =payload1;
    }

    std::vector<unsigned char> BaseMessage::Serialize() {
        std::vector<unsigned char> ret;
        std::vector<unsigned char> val;
        val=header.Serialize();
        ret.insert(ret.end(),val.begin(),val.end());
        if(payload!= nullptr) {
            val = payload->Serialize();
            ret.insert(ret.end(), val.begin(), val.end());
        }
        return ret;
    }


}
