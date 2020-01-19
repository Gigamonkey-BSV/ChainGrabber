// Copyright (c) 2019 Katrina Swales
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include <iostream>
#include <chainGrabber/Database.h>
#include <chainGrabber/MongoDatabase.h>
#include <chainGrabber/DatabaseComponent.h>
#include <chainGrabber/ConfigurationManager.h>
#include <chainGrabber/ConfigurationManagerJSON.h>
#include "Hypodermic/Hypodermic.h"
int main(int ac,char** av) {
    Hypodermic::ContainerBuilder builder;
    builder.registerType<chain_grabber::ConfigurationManagerJSON>().as<chain_grabber::ConfigurationManager>().singleInstance();
    builder.registerType<chain_grabber::MongoDatabase>().as<chain_grabber::Database>();
    auto container=builder.build();
    container->resolve<chain_grabber::ConfigurationManager>()->loadConfigs(ac,av);
    auto database=container->resolve<chain_grabber::Database>();
    database->connect();

    return 0;
}