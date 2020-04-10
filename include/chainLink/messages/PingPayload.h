// Copyright (c) 2020 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CHAIN_GRABBER_PINGMESSAGE_H
#define CHAIN_GRABBER_PINGMESSAGE_H

#include <ostream>
#include "Payload.h"

namespace chain_link::messages {
    class Pong;
    class Ping : public Payload {
    public:
        Ping(const Ping& ping);
        Ping();

        static std::shared_ptr<Ping> Deserialize(std::vector<unsigned char>::iterator& data);

        friend std::ostream &operator<<(std::ostream &os, const Ping &ping);

        bool operator==(const Pong &rhs) const;
        [[nodiscard]] uint64_t getNonce() const {
            return nonce;
        }
        void setNonce(uint64_t newNonce) {
            this->nonce=newNonce;
        }
        std::vector<unsigned char> Serialize() override;

        Ping *Clone() override;

    private:
        uint64_t nonce{};
    };
}
#endif //CHAIN_GRABBER_PINGMESSAGE_H
