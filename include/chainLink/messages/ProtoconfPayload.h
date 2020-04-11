// Copyright (c) 2020 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CHAIN_GRABBER_PROTOCONFPAYLOAD_H
#define CHAIN_GRABBER_PROTOCONFPAYLOAD_H

#include <ostream>
#include "Payload.h"
namespace chain_link::messages {

    class Protoconf : public Payload {
    public:
        Protoconf(const Protoconf& protoconf);
        Protoconf();

        static std::shared_ptr<Protoconf> Deserialize(std::vector<unsigned char>::iterator& data);


        std::vector<unsigned char> Serialize() override;

        Protoconf *Clone() override;

        friend std::ostream &operator<<(std::ostream &os, const Protoconf &protoconf);

    private:
        uint64_t number_of_fields{};
        uint32_t max_recv_payload_length{};
    };
}
#endif //CHAIN_GRABBER_PROTOCONFPAYLOAD_H
