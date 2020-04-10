// Copyright (c) 2020 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainLink/messages/PongPayload.h"
#include "chainLink/Utils.h"

namespace chain_link::messages {
    std::shared_ptr<Pong> Pong::Deserialize(std::vector<unsigned char>::iterator &data) {
        std::shared_ptr<Pong> pong=std::make_shared<Pong>();
        bitsToInt<uint64_t >(pong->nonce,std::vector<unsigned char>(data,data+8));
        return pong;
    }

    std::vector<unsigned char> Pong::Serialize() {
        std::vector<unsigned char> ret;
        std::vector<unsigned char> val;
        val=intToBits<uint64_t >(nonce);
        ret.insert(ret.end(),val.begin(),val.end());
        return ret;
    }

    Pong::Pong(const Pong &pong) {
        this->nonce=pong.nonce;
    }

    Pong *Pong::Clone() {
        return nullptr;
    }

    bool Pong::operator==(const Ping &rhs) const {
        return false;
    }

    Pong::Pong() = default;
}

