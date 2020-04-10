// Copyright (c) 2020 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CHAIN_GRABBER_PONGPAYLOAD_H
#define CHAIN_GRABBER_PONGPAYLOAD_H
#include "Payload.h"

namespace chain_link::messages {
    class Ping;
    class Pong : public Payload {
    public:
        Pong(const Pong& pong);
        Pong();
        [[nodiscard]] uint64_t getNonce() const {
            return nonce;
        }
        static std::shared_ptr<Pong> Deserialize(std::vector<unsigned char>::iterator& data);



        bool operator==(const Ping &rhs) const;

        std::vector<unsigned char> Serialize() override;

        Pong *Clone() override;

    private:
        uint64_t nonce{};
    };
}
#endif //CHAIN_GRABBER_PONGPAYLOAD_H
