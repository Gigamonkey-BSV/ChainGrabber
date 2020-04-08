// Copyright (c) 2019 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainLink/Utils.h>
#include "chainLink/messages/RejectPayload.h"
namespace chain_link::messages {

    RejectPayload::RejectPayload(const RejectPayload &version1) {
            message=version1.message;
            code=version1.code;
            reason=version1.reason;
            if(version1.extra!=nullptr) {
                extra=new unsigned char[32];
                for(int i=0;i<32;i++) {
                    extra[i]=version1.extra[i];
                }
            }
    }

    RejectPayload::RejectPayload() {
        extra= nullptr;
    }

    std::vector<unsigned char> RejectPayload::Serialize() {
        std::vector<unsigned char> ret;
        std::vector<unsigned char> val;
        val=getVarIntBytes(message.size());
        ret.insert(ret.end(),val.begin(),val.end());
        for(char i : message)
            ret.push_back(i);
        ret.push_back(code);
        val=getVarIntBytes(reason.size());
        ret.insert(ret.end(),val.begin(),val.end());
        for(char i : reason)
            ret.push_back(i);
        if(extra!= nullptr)
        {
            for(int i=0;i<32;i++)
                ret.push_back(extra[i]);
        }
    }

    RejectPayload RejectPayload::Deserialize(std::vector<unsigned char>::iterator &data,std::vector<unsigned char>::iterator& end) {
        RejectPayload reject;
        uint64_t  size=getVarInt(data);
        for(int i=0;i<size;i++)
            reject.message.push_back(*data++);
        reject.code=*data++;
        size=getVarInt(data);
        for(int i=0;i<size;i++)
            reject.reason.push_back(*data++);

        if(data!=end) {
            reject.extra=new unsigned char[32];
            for (int i = 0; i < 32; i++) {
                if (data != end)
                    reject.extra[i]=*data++;
                else
                    reject.extra[i]=0x00;
            }
        } else
            reject.extra=nullptr;

        return reject;
    }

    std::ostream &operator<<(std::ostream &os, const RejectPayload &payload) {
        os << " message: " << payload.message << " code: " << payload.code
           << " reason: " << payload.reason << " extra: " << payload.extra;
        return os;
    }

    bool RejectPayload::operator==(const RejectPayload &rhs) const {
        return std::tie( message, code, reason, extra) ==
               std::tie(rhs.message, rhs.code, rhs.reason,
                        rhs.extra);
    }

    bool RejectPayload::operator!=(const RejectPayload &rhs) const {
        return !(rhs == *this);
    }
}

