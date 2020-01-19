// Copyright (c) 2019 Katrina Swales
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CHAIN_GRABBER_MOCKDATABASEIMPL_H
#define CHAIN_GRABBER_MOCKDATABASEIMPL_H

#include <map>
#include "chainGrabber/Database.h"
namespace chain_grabber::tests {
    class MockDatabaseImpl : public Database {
        MockDatabaseImpl()= default;

    public:
        std::string InsertHeader(header header) override;

        header GetHeader(std::string id) override;

        header FindHeaderByMerkle(std::string hash) override;

        header FindHeaderByHash(std::string hash) override;

        void connect() override;

    private:
        std::map<std::string,header> headers;
        int curId=0;
    };



}

#endif //CHAIN_GRABBER_MOCKDATABASEIMPL_H
