// Copyright (c) 2019 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CHAIN_GRABBER_CONSTANTS_H
#define CHAIN_GRABBER_CONSTANTS_H

#include <array>

namespace chain_link {
    class Config {
        class ConfigBase {
        public:
            std::array<unsigned char, 4> GetMagicBytes() { return magicBytes;}
            std::string GetPort() { return port;}

        protected:
            std::array<unsigned char, 4> magicBytes;
            std::string port;
        };
        class MainNetConfig : public ConfigBase {
        public:
            MainNetConfig();
        };
        class TestNetConfig : public ConfigBase {
            public:
            TestNetConfig();
        };
    public:
        static Config::ConfigBase config;
    public:
        static Config::ConfigBase getConfig();
        static void SetMainNet() {
            config=MainNetConfig();
        }
        static void SetTestNet() {
            config=TestNetConfig();
        }
    };

}
#endif //CHAIN_GRABBER_CONSTANTS_H
