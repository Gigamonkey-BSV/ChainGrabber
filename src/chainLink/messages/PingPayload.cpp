// Copyright (c) 2020 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainLink/messages/PongPayload.h>
#include "chainLink/messages/PingPayload.h"
#include "chainLink/Utils.h"

namespace chain_link::messages {

    std::vector<unsigned char> Ping::Serialize() {
        std::vector<unsigned char> ret;
        std::vector<unsigned char> val;
        val=intToBits<uint64_t >(nonce);
        ret.insert(ret.end(),val.begin(),val.end());
        return ret;
    }

    Ping *Ping::Clone() {
        return nullptr;
    }

    Ping::Ping(const Ping &ping) {
        this->nonce=ping.nonce;
    }

    Ping::Ping() = default;

    std::shared_ptr<Ping> Ping::Deserialize(std::vector<unsigned char>::iterator &data) {
        std::shared_ptr<Ping> ping=std::make_shared<Ping>();
        bitsToInt<uint64_t >(ping->nonce,std::vector<unsigned char>(data,data+8));
        return ping;
    }

    std::ostream &operator<<(std::ostream &os, const Ping &ping) {
        os << "Ping: " << " nonce: " << ping.nonce;
        return os;
    }

    bool Ping::operator==(const Pong &rhs) const {
        return nonce==rhs.getNonce();
    }


}

