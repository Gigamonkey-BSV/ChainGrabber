//
// Created by nekosune on 18/01/2020.
//

#include "chainGrabber/ConfigurationManagerJSON.h"
#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <iostream>
#include <iterator>
#include <fstream>
#include <iomanip>
#include "chainLink/Network.h"

namespace chain_grabber {

    std::string ConfigurationManagerJSON::getString(std::string configName) {
        if(vm.count(configName) && ! vm[configName].defaulted())
            return vm[configName].as<std::string>();
        else if(!configFile[configName].is_null() && configFile[configName].is_string())
            return configFile[configName];
        else
            return "";
    }

    int ConfigurationManagerJSON::getInt(std::string configName) {
        if(vm.count(configName) && ! vm[configName].defaulted())
            return vm[configName].as<int>();
        else if(!configFile[configName].is_null() && configFile[configName].is_number_integer())
            return configFile[configName];
        else
            return -1;
    }

    void ConfigurationManagerJSON::loadConfigs(int ac, char **av) {
        if(setup)
            return;
        po::options_description desc("Options for Chain Grabber");
        desc.add_options()
                ("help","produce help message")
                ("configFile",po::value<std::string>()->default_value("./config.json"),"Config file location")
                ("connectionString",po::value<std::string>()->default_value("mongodb://localhost:27017"),"connection string for mongodb")
                ("net",po::value<std::string>()->default_value("main"),"Which network should this use")
                ;
        po::store(po::parse_command_line(ac,av,desc),vm);
        po::notify(vm);
        if (vm.count("help")) {
            std::cout << desc << std::endl;
            exit(0);
        }
        if(vm.count("configFile"))
        {
            std::ifstream i(vm["configFile"].as<std::string>());
            if(i.good())
                i >> configFile;
            else{
                configFile["connectionString"] = vm["connectionString"].as<std::string>();
                configFile["net"] = vm["net"].as<std::string>();
                std::ofstream o(vm["configFile"].as<std::string>());
                o << std::setw(4) <<configFile << std::endl;
                o.close();
            }
        }
        else {
            throw  std::runtime_error("no config file found");
        }

        setup=true;

    }

    Network ConfigurationManagerJSON::getNetwork() {
        if(vm.count("net") && ! vm["net"].defaulted())
            return vm["net"].as<std::string>() == "main" ? Network::MainNet : Network::TestNet;
        else if(!configFile["net"].is_null() )
            return configFile["net"]== "main" ? Network::MainNet : Network::TestNet;
        else
            return Network::MainNet;
    }
}