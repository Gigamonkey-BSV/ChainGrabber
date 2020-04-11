// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainLink/messages/ProtoconfPayload.h>
#include "chainLink/Utils.h"

namespace chain_link::messages {

    Protoconf::Protoconf(const Protoconf& protoconf ) {
        this->max_recv_payload_length=protoconf.max_recv_payload_length;
        this->number_of_fields=protoconf.number_of_fields;
    }
    Protoconf::Protoconf() {

    }

    std::shared_ptr<Protoconf> Protoconf::Deserialize(std::vector<unsigned char>::iterator &data) {
        std::shared_ptr<Protoconf> protoconf=std::make_shared<Protoconf>();
        protoconf->number_of_fields=getVarInt(data);
        bitsToInt<uint32_t >(protoconf->max_recv_payload_length,std::vector<unsigned char>(data,data+4));
        return protoconf;
    }

    std::vector<unsigned char> Protoconf::Serialize() {
        std::vector<unsigned char> ret;
        std::vector<unsigned char> val;
        val=getVarIntBytes(number_of_fields);
        ret.insert(ret.end(),val.begin(),val.end());
        val=intToBits<uint32_t >(max_recv_payload_length);
        ret.insert(ret.end(),val.begin(),val.end());
        return ret;
    }

    Protoconf *Protoconf::Clone() {
        return nullptr;
    }

    std::ostream &operator<<(std::ostream &os, const Protoconf &protoconf) {
        os << "protoconf: " << " number_of_fields: " << protoconf.number_of_fields
           << " max_recv_payload_length: " << protoconf.max_recv_payload_length;
        return os;
    }


}