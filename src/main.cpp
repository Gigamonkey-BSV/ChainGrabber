// Copyright (c) 2019 Katrina Swales
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <iostream>
#include <chainGrabber/Database.h>
#include <chainGrabber/MongoDatabase.h>

#include <chainGrabber/ConfigurationManager.h>
#include <chainGrabber/ConfigurationManagerJSON.h>
#include <chainGrabber/WhatsOnChainAPI.h>
#include "Hypodermic/Hypodermic.h"
auto config = std::make_shared<chain_grabber::ConfigurationManagerJSON>(chain_grabber::ConfigurationManagerJSON());

int main(int ac,char** av) {

    config->loadConfigs(ac,av);

    Hypodermic::ContainerBuilder builder;
    builder.registerType<chain_grabber::ConfigurationManagerJSON>().as<chain_grabber::ConfigurationManager>().singleInstance();
    builder.registerInstance(config);
    builder.registerType<chain_grabber::MongoDatabase>().as<chain_grabber::Database>();
    builder.registerType<chain_grabber::WhatsOnChainAPI>().as<chain_grabber::BitcoinAPI>();
    auto container=builder.build();
    container->resolve<chain_grabber::ConfigurationManager>()->loadConfigs(ac,av);
    auto database=container->resolve<chain_grabber::Database>();
    database->connect();
    chain_grabber::header test_header();
    auto api = container->resolve<chain_grabber::BitcoinAPI>();
    std::cout << api->GetHeadBlockHash() << std::endl;



    return 0;
}