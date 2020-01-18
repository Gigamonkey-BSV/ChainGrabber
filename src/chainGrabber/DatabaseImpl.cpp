// Copyright (c) 2019 Katrina Swales
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainGrabber/DatabaseImpl.h"

int chain_grabber::DatabaseImpl::InsertHeader(chain_grabber::header header) {
    return 0;
}

chain_grabber::header chain_grabber::DatabaseImpl::GetHeader(int id) {
    return header();
}

chain_grabber::header chain_grabber::DatabaseImpl::FindHeaderByMerkle(std::string hash) {
    return header();
}

chain_grabber::header chain_grabber::DatabaseImpl::FindHeaderByHash(std::string hash) {
    return header();
}

fruit::Component<chain_grabber::Database> chain_grabber::getDatabaseComponent() {
        return fruit::createComponent()
                .bind<Database, DatabaseImpl>();
    }
