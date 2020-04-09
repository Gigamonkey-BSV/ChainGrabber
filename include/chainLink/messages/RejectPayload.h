// Copyright (c) 2019 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef CHAIN_GRABBER_REJECTPAYLOAD_H
#define CHAIN_GRABBER_REJECTPAYLOAD_H
#include <ostream>
#include "chainLink/messages/Payload.h"
#include "chainLink/Address.h"
namespace chain_link::messages {
    class RejectPayload : public Payload {
    public:
        RejectPayload(const RejectPayload& version1);
        RejectPayload();
        std::string message;
        unsigned char code{};
        std::string reason;
        unsigned char* extra;
        std::vector<unsigned char> Serialize() override;
        static RejectPayload Deserialize(std::vector<unsigned char>::iterator& begin,std::vector<unsigned char>::iterator& end);

        friend std::ostream &operator<<(std::ostream &os, const RejectPayload &payload);

        bool operator==(const RejectPayload &rhs) const;

        bool operator!=(const RejectPayload &rhs) const;

        Payload *Clone() override;
    };
}
#endif //CHAIN_GRABBER_REJECTPAYLOAD_H
