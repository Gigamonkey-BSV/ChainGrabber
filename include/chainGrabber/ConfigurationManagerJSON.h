//
// Created by nekosune on 18/01/2020.
//

#ifndef CHAIN_GRABBER_CONFIGURATIONMANAGERJSON_H
#define CHAIN_GRABBER_CONFIGURATIONMANAGERJSON_H

#include "ConfigurationManager.h"
#include <nlohmann/json.hpp>
#include <boost/program_options.hpp>
#include <boost/program_options/variables_map.hpp>

namespace po = boost::program_options;

namespace chain_grabber {
    class ConfigurationManagerJSON : public ConfigurationManager {
    public:
        ConfigurationManagerJSON()= default;
        std::string getString(std::string configName) override;

        int getInt(std::string configName) override;

        Network getNetwork() override;

        void loadConfigs(int ac, char **av) override;

    private:
        nlohmann::json configFile;
        po::variables_map vm;
        bool setup=false;

    };
}


#endif //CHAIN_GRABBER_CONFIGURATIONMANAGERJSON_H
