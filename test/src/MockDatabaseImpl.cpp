// Copyright (c) 2019 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "MockDatabaseImpl.h"

std::string chain_grabber::tests::MockDatabaseImpl::InsertHeader(chain_grabber::header header) {
    std::string id=std::to_string(curId++);
    headers.insert(std::make_pair(id,header));
    return id;
}

chain_grabber::header chain_grabber::tests::MockDatabaseImpl::GetHeader(std::string id) {
    return headers[id];
}

chain_grabber::header chain_grabber::tests::MockDatabaseImpl::FindHeaderByMerkle(std::string hash) {
    for (auto const& cur : headers) {
        if(cur.second.MerkleRoot ==hash)
            return cur.second;
    }
    return header() ;
}

chain_grabber::header chain_grabber::tests::MockDatabaseImpl::FindHeaderByHash(std::string hash) {
    for (auto const& cur : headers) {
        if(cur.second.Hash ==hash)
            return cur.second;
    }
    return header() ;
}

void chain_grabber::tests::MockDatabaseImpl::connect() {

}

