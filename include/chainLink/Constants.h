//
// Created by nekosune on 24/02/2020.
//

#ifndef CHAIN_GRABBER_CONSTANTS_H
#define CHAIN_GRABBER_CONSTANTS_H

#include <array>

namespace chain_link {
    class Config {
        class ConfigBase {
        public:
            std::array<uint8_t, 4> GetMagicBytes() { return magicBytes;}
            int GetPort() { return port;}

        protected:
            std::array<uint8_t, 4> magicBytes;
            int port;
        };
        class MainNetConfig : public ConfigBase {
        public:
            MainNetConfig();
        };
        class TestNetConfig : public ConfigBase {
            public:
            TestNetConfig();
        };
    private:
        static Config::ConfigBase config;
    public:
        static Config::ConfigBase getConfig() {
            return config;
        }
        static void SetMainNet() {
            config=MainNetConfig();
        }
        static void SetTestNet() {
            config=TestNetConfig();
        }
    };
}
#endif //CHAIN_GRABBER_CONSTANTS_H
