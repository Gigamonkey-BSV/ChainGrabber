// Copyright (c) 2019 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainLink/messages/MessageHeader.h>
#include <chainLink/messages/VersionPayload.h>
#include <chainLink/messages/BaseMessage.h>
#include "chainLink/Address.h"
#include "testUtils.h"
#include "gtest/gtest.h"

class MessageTest : public ::testing::Test {
protected:
    void SetUp() override {
        auto itr=headerPacket.begin();
        header1=chain_link::messages::MessageHeader::Deserialize(itr);
        itr=payloadPacket.begin();
        version1=chain_link::messages::Version::Deserialize(itr);
        message1.header=header1;
        message1.payload=&version1;
    }
    std::vector<unsigned char> headerPacket=strToTestVector("e3e1f3e876657273696f6e00000000006800000005f178c7");
    std::vector<unsigned char> payloadPacket=strToTestVector("7f1101002500000000000000c02f6e5e00000000000000000000000000000000000000000000ffff5c183534b03c25000000000000000000000000000000000000000000000000003933dcf677284ed6122f426974636f696e2053563a312e302e322f998e090001e3e1f3e876657261636b000000000000000000005df6e0e2");
    chain_link::messages::MessageHeader header1;
    chain_link::messages::Version version1;
    chain_link::messages::BaseMessage message1;
};

TEST_F(MessageTest,TestValidity) {

    EXPECT_TRUE(message1.isValid());
}

TEST_F(MessageTest,TestInValidity) {
    dynamic_cast<chain_link::messages::Version*>(message1.payload)->user_agent="/Hackerman9000:0/";
    EXPECT_FALSE(message1.isValid());
}
TEST_F(MessageTest,InitializeMessage) {
    chain_link::messages::BaseMessage message=chain_link::messages::BaseMessage::MakeMessage("version",version1);
    EXPECT_TRUE(message.isValid());

}