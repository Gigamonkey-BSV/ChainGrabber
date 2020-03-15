// Copyright (c) 2019 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainLink/Address.h"
#include "chainLink/messages/VersionPayload.h"
#include "testUtils.h"
#include "gtest/gtest.h"

class VersionTest : public ::testing::Test {
protected:
    void SetUp() override {
        // version: 70015 services: 37 timestamp: 1584266481 addr_to: services: 0 timestamp: 0
        // ip: ::ffff:92.24.53.52 port: 41690 initial_: 1 addr_from: services: 1 timestamp: 0
        // ip: ::ffff:0.0.0.0 port: 0 initial_: 1 nonce: 9056541416301440308
        // user_agent: /python-mininode-tester:0.0.3/ start_height: -1 relay: 1
        version1.version=70015;
        version1.services=37;
        version1.timestamp = 1584266481;
        version1.addr_from=chain_link::Address(true);
        version1.addr_from.services=1;
        version1.addr_from.ip[0]=version1.addr_from.ip[1]=version1.addr_from.ip[2]=version1.addr_from.ip[3]=version1.addr_from.ip[4]=version1.addr_from.ip[5]=
        version1.addr_from.ip[6]=version1.addr_from.ip[7]=version1.addr_from.ip[8]=version1.addr_from.ip[9]=0x00;
        version1.addr_from.ip[10] = 0xff;
        version1.addr_from.ip[11] = 0xff;
        version1.addr_from.ip[12] = 0x00;
        version1.addr_from.ip[13] = 0x00;
        version1.addr_from.ip[14] = 0x00;
        version1.addr_from.ip[15] = 0x00;
        version1.addr_from.timestamp=0;
        //92.24.53.52
        version1.addr_from.port=0;
        version1.addr_to=chain_link::Address(true);
        version1.addr_to.services=0;
        version1.addr_to.ip[0]=version1.addr_to.ip[1]=version1.addr_to.ip[2]=version1.addr_to.ip[3]=version1.addr_to.ip[4]=version1.addr_to.ip[5]=
        version1.addr_to.ip[6]=version1.addr_to.ip[7]=version1.addr_to.ip[8]=version1.addr_to.ip[9]=0x00;
        version1.addr_to.ip[10] = 0xff;
        version1.addr_to.ip[11] = 0xff;
        version1.addr_to.ip[12] = 92;
        version1.addr_to.ip[13] = 24;
        version1.addr_to.ip[14] = 53;
        version1.addr_to.ip[15] = 52;
        version1.addr_to.timestamp=0;
        version1.addr_to.port=41690;
        version1.nonce = 9056541416301440308;
        version1.user_agent = "/python-mininode-tester:0.0.3/";
        version1.start_height=-1;
        version1.relay=true;

        address1=chain_link::Address(true);
        address1.port =24711;
        address1.services=0;
        address1.timestamp=0;

        //0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ff, ff, 5c, 18, 34, 56
        address1.ip[0]=address1.ip[1]=address1.ip[2]=address1.ip[3]=address1.ip[4]=address1.ip[5]=
        address1.ip[6]=address1.ip[7]=address1.ip[8]=address1.ip[9]=0x00;
        address1.ip[10] = 0xff;
        address1.ip[11] = 0xff;
        address1.ip[12] = 0x5c;
        address1.ip[13] = 0x18;
        address1.ip[14] = 0x34;
        address1.ip[15] = 0x56;
    }
    std::vector<unsigned char> testPacket=strToTestVector("7f1101002500000000000000f1fc6d5e00000000000000000000000000000000000000000000ffff5c183534a2da010000000000000000000000000000000000ffff00000000000034ad423c6f4caf7d1e2f707974686f6e2d6d696e696e6f64652d7465737465723a302e302e332fffffffff01");
    chain_link::Address address1;
    chain_link::messages::Version version1;
};
TEST_F(VersionTest,TestDeserialize) {
    auto itr=testPacket.begin();
    chain_link::messages::Version testVersion=chain_link::messages::Version::Deserialize(itr);
    std::cout << testVersion << std::endl;
    EXPECT_EQ(version1,testVersion);

}

TEST_F(VersionTest,TestSerialize) {
    EXPECT_EQ(testPacket,version1.Serialize());
}