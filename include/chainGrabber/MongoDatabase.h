// Copyright (c) 2019 Katrina Swales
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CHAIN_GRABBER_MONGODATABASE_H
#define CHAIN_GRABBER_MONGODATABASE_H

#include "chainGrabber/Database.h"
#include "ConfigurationManager.h"
#include <fruit/fruit.h>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>
namespace  chain_grabber {
    class MongoDatabase : public Database {
    private:
        std::shared_ptr<ConfigurationManager> config;
        mongocxx::instance instance;
        mongocxx::client client;
        static chain_grabber::header documentToStruct(bsoncxx::document::view view);
    public:
        MongoDatabase(std::shared_ptr<ConfigurationManager> config)
        :config(config), instance{} {

        };

        void connect() override;

        std::string InsertHeader(header header) override;

        header GetHeader(std::string id) override;

        header FindHeaderByMerkle(std::string hash) override;

        header FindHeaderByHash(std::string hash) override;


    };

    fruit::Component<fruit::Required<chain_grabber::ConfigurationManager>,Database> getMongoDatabaseComponent();
}


#endif //CHAIN_GRABBER_MONGODATABASE_H
