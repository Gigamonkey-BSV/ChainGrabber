// Copyright (c) 2019 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainLink/messages/VersionPayload.h"
#include "chainLink/Utils.h"
namespace chain_link::messages {

    std::vector<unsigned char> Version::Serialize() {
        std::vector<unsigned char> ret;
        std::vector<unsigned char> val;
        val=intToBits<int32_t>(version);
        ret.insert(ret.end(),val.begin(),val.end());
        val=intToBits<uint64_t >(services);
        ret.insert(ret.end(),val.begin(),val.end());
        val=intToBits<int64_t >(timestamp);
        ret.insert(ret.end(),val.begin(),val.end());
        val=addr_to.Serialize();
        ret.insert(ret.end(),val.begin(),val.end());

        if(version>=106) {
            val=addr_from.Serialize();
            ret.insert(ret.end(),val.begin(),val.end());
            val=intToBits<uint64_t >(nonce);
            ret.insert(ret.end(),val.begin(),val.end());
            val=getVarIntBytes(user_agent.length());
            ret.insert(ret.end(),val.begin(),val.end());
            for(char i : user_agent) {
                ret.push_back(i);
            }

        }
        if(version>=209) {
            val=intToBits<int32_t >(start_height);
            ret.insert(ret.end(),val.begin(),val.end());
        }

        if(version>=70001) {
            ret.push_back(relay);
        }
        return ret;
    }

    Version Version::Deserialize(std::vector<unsigned char>::iterator& data) {
        Version version;
        bitsToInt<int32_t>(version.version,std::vector<unsigned char>(data,data+4));
        data+=4;
        bitsToInt<uint64_t>(version.services,std::vector<unsigned char>(data,data+8));
        data+=8;
        bitsToInt<int64_t>(version.timestamp,std::vector<unsigned char>(data,data+8));
        data+=8;
        version.addr_to=chain_link::Address::DeSerialize(data,true);
        if(version.version>=106) {
            version.addr_from=chain_link::Address::DeSerialize(data,true);
            bitsToInt<uint64_t>(version.nonce,std::vector<unsigned char>(data,data+8));
            data+=8;
            uint64_t user_agent_size=getVarInt(data);
            std::vector<char> user_agent_vector;
            for(int i=0;i<user_agent_size;i++) {
                user_agent_vector.push_back(*data++);
            }
            version.user_agent=std::string(user_agent_vector.begin(),user_agent_vector.end());
        } else
        {
            version.addr_from= chain_link::Address();
            version.nonce=0;
            version.user_agent="";
            version.start_height=0;
        }
        if(version.version>=209) {
            bitsToInt<int32_t>(version.start_height,std::vector<unsigned char>(data,data+4));
            data+=4;
        }
        if(version.version>=70001) {
            try {
                version.relay=*data++ == 1;
            }
            catch(std::exception& e)
            {
                version.relay= false;
            }
        } else{
            version.relay=false;
        }


        return version;
    }

    std::ostream &operator<<(std::ostream &os, const Version &version) {
        os  << " version: " << version.version << " services: "
           << version.services << " timestamp: " << version.timestamp << " addr_to: " << version.addr_to
           << " addr_from: " << version.addr_from << " nonce: " << version.nonce << " user_agent: "
           << version.user_agent << " start_height: " << version.start_height << " relay: " << version.relay;
        return os;
    }

    bool Version::operator==(const Version &rhs) const {
        return std::tie( version, services, timestamp,
                        addr_to, addr_from, nonce, user_agent, start_height, relay) ==
               std::tie( rhs.version, rhs.services,
                        rhs.timestamp, rhs.addr_to, rhs.addr_from, rhs.nonce, rhs.user_agent, rhs.start_height,
                        rhs.relay);
    }

    bool Version::operator!=(const Version &rhs) const {
        return !(rhs == *this);
    }
}