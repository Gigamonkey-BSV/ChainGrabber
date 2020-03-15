// Copyright (c) 2019 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "gtest/gtest.h"
#include "testUtils.h"

TEST(TestUtils,TestStringToHex) {
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
    std::vector<unsigned char> test2=strToTestVector("000000000000000000000000000000000000ffff5c1834568760");
    EXPECT_EQ(test,test2);
}

std::vector<unsigned char> strToTestVector(std::string input) {
    std::vector<unsigned char> ret;
    if (input.size() % 2 != 0) {
        return ret;
    }
    for (int i = 0; i < input.size(); i += 2) {
        ret.push_back(std::stoi(input.substr(i, 2), nullptr, 16));
    }
    return ret;
}
