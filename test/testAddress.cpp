// Copyright (c) 2019 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainLink/Address.h"
#include "testUtils.h"
#include "gtest/gtest.h"

class AddressTest : public ::testing::Test {
protected:
    void SetUp() override {
        address1=chain_link::Address(true);
        address1.port =34656;
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
    std::vector<unsigned char> testPacket=strToTestVector("000000000000000000000000000000000000ffff5c1834568760");
    chain_link::Address address1;
};

TEST_F(AddressTest,TestDeserialize) {

    auto itr=testPacket.begin();
    chain_link::Address addr=chain_link::Address::DeSerialize(itr,true);

    EXPECT_EQ(addr,address1);
}
TEST_F(AddressTest,TestSerialize) {
    EXPECT_EQ(testPacket,address1.Serialize());

}