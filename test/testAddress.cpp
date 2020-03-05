// Copyright (c) 2019 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainLink/Address.h"

#include "gtest/gtest.h"
TEST(TestAddress,TestDeserialize) {
    std::vector<unsigned char> test;
    // 00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:ff:ff:5c:18:34:56:87:60
    test.push_back((unsigned char)0x00);
    test.push_back((unsigned char)0x00);
    test.push_back((unsigned char)0x00);
    test.push_back((unsigned char)0x00);
    test.push_back((unsigned char)0x00);
    test.push_back((unsigned char)0x00);
    test.push_back((unsigned char)0x00);
    test.push_back((unsigned char)0x00);
    test.push_back((unsigned char)0x00);
    test.push_back((unsigned char)0x00);
    test.push_back((unsigned char)0x00);
    test.push_back((unsigned char)0x00);
    test.push_back((unsigned char)0x00);
    test.push_back((unsigned char)0x00);
    test.push_back((unsigned char)0x00);
    test.push_back((unsigned char)0x00);
    test.push_back((unsigned char)0x00);
    test.push_back((unsigned char)0x00);
    test.push_back((unsigned char)0xff);
    test.push_back((unsigned char)0xff);
    test.push_back((unsigned char)0x5c);
    test.push_back((unsigned char)0x18);
    test.push_back((unsigned char)0x34);
    test.push_back((unsigned char)0x56);
    test.push_back((unsigned char)0x87);
    test.push_back((unsigned char)0x60);
    chain_link::Address addr=chain_link::Address::DeSerialize(test,true);

    std::cout << addr << std::endl;
}
