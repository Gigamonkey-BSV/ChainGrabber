// Copyright (c) 2019 Katrina Swales
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CHAIN_GRABBER_DATABASEIMPL_H
#define CHAIN_GRABBER_DATABASEIMPL_H

#include "chainGrabber/Database.h"
#include <fruit/fruit.h>
namespace  chain_grabber {
    class DatabaseImpl : public Database {
    public:
        INJECT(DatabaseImpl()) = default;

        int InsertHeader(header header) override;

        header GetHeader(int id) override;

        header FindHeaderByMerkle(std::string hash) override;

        header FindHeaderByHash(std::string hash) override;
    };

    fruit::Component<Database> getDatabaseComponent();
}


#endif //CHAIN_GRABBER_DATABASEIMPL_H
