// Copyright (c) 2019 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "chainLink/Address.h"
#include "chainLink/Utils.h"
namespace chain_link {

    Address Address::DeSerialize(std::vector<unsigned char> data,bool initial) {
        auto itr=data.begin();
        Address addr(initial);
        bitsToInt<uint64_t>(addr.services,std::vector<unsigned char>(itr,itr+8));
        itr+=8;
        if(!initial) {
            bitsToInt<int64_t>(addr.timestamp,std::vector<unsigned char>(itr,itr+8));
            itr+=8;
        }
        for(unsigned char & i : addr.ip) {
            i = *itr++;
        }
        bitsToInt<uint16_t>(addr.port,std::vector<unsigned char>(itr,itr+2));
        return addr;
    }

    std::vector<unsigned char> Address::Serialize() {
        return std::vector<unsigned char>();
    }

    Address::Address(bool initial) {
        this->initial_=initial;
        this->port=0;
        this->services=0;
        this->timestamp=0;
    }

    std::ostream &operator<<(std::ostream &os, const Address &address) {
        char ipstr[INET6_ADDRSTRLEN];
        inet_ntop(AF_INET6,address.ip,ipstr,sizeof(ipstr));
        os << "services: " << address.services << " timestamp: " << address.timestamp << " ip: " << ipstr
           << " port: " << address.port << " initial_: " << address.initial_;
        return os;
    }
}
