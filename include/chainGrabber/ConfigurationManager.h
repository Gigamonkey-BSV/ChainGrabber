// Copyright (c) 2019 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CHAIN_GRABBER_CONFIGURATIONMANAGER_H
#define CHAIN_GRABBER_CONFIGURATIONMANAGER_H
#include <string>
#include "chainLink/Network.h"

namespace chain_grabber {
    class ConfigurationManager {
    public:
        virtual std::string getString(std::string configName) = 0;
        virtual int getInt(std::string configName) = 0;
        virtual Network getNetwork() = 0;
        virtual void loadConfigs(int ac, char* av[]) = 0;
    };

}


#endif //CHAIN_GRABBER_CONFIGURATIONMANAGER_H
