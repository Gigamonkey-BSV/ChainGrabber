// Copyright (c) 2019 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainLink/messages/MessageHeader.h>
#include "chainLink/Address.h"
#include "testUtils.h"
#include "gtest/gtest.h"
#include "chainLink/Constants.h"

//e3e1f3e876657273696f6e00000000006800000005f178c
class HeaderTest : public ::testing::Test {
protected:
    void SetUp() override {
        chain_link::Config::SetMainNet();
        header1.MagicBytes = chain_link::Config::getConfig().GetMagicBytes();
        header1.setCommand("version");
        header1.PayloadSize = 0x68;
        header1.Checksum = {5, 0xf1, 0x78, 0xc7};
    }
    std::vector<unsigned char> testPacket=strToTestVector("e3e1f3e876657273696f6e00000000006800000005f178c7");
    chain_link::messages::MessageHeader header1;

};
TEST_F(HeaderTest,TestHeaderDeserialize) {
    auto itr=testPacket.begin();
    chain_link::messages::MessageHeader header=chain_link::messages::MessageHeader::Deserialize(itr);
    EXPECT_EQ(header,header1);

}

TEST_F(HeaderTest,TestHeaderSerialize) {
    EXPECT_EQ(testPacket,header1.Serialize());
}