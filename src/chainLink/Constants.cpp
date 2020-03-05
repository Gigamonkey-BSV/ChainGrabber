// Copyright (c) 2019 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainLink/Constants.h"

namespace chain_link {


    Config::MainNetConfig::MainNetConfig() {
        magicBytes[0]=0xe3;
        magicBytes[1] = 0xe1;
        magicBytes[2] = 0xf3;
        magicBytes[3] = 0xe8;
        port = 8333;
    }
    Config::TestNetConfig::TestNetConfig() {
        magicBytes[0]=0xf4;
        magicBytes[1] = 0xe5;
        magicBytes[2] = 0xf3;
        magicBytes[3] = 0xf4;
        port = 18333;
    }


}
