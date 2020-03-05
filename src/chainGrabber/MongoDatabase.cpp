// Copyright (c) 2019 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainGrabber/MongoDatabase.h"
using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

std::string chain_grabber::MongoDatabase::InsertHeader(chain_grabber::header header) {
    mongocxx::database db = client["gigamonkey"];
    mongocxx::collection coll = db["headers"];
    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::document::value doc_value = builder
            << "height" << header.Height
            << "version" << header.Version
            << "hash" << header.Height
            << "previous" << header.Previous
            << "merkleRoot" << header.MerkleRoot
            << "timestamp" << header.Timestamp
            << "target" << header.Target
            << "nonce" << header.Nonce
            << bsoncxx::builder::stream::finalize;
    bsoncxx::document::view view = doc_value.view();
    bsoncxx::stdx::optional<mongocxx::result::insert_one> result =
            coll.insert_one(doc_value.view());
    if (result) {
        if (result.value().result().inserted_count() > 0)
            return result.value().inserted_id().get_oid().value.to_string();
        else
            return "";
    } else
        return "";
}

chain_grabber::header chain_grabber::MongoDatabase::GetHeader(std::string id) {
    mongocxx::database db = client["gigamonkey"];
    mongocxx::collection coll = db["headers"];
    bsoncxx::stdx::optional<bsoncxx::document::value> maybe_result =
            coll.find_one(document{} << "_id" << id << finalize);
    if(maybe_result) {
        return documentToStruct(maybe_result->view());
    }
}

chain_grabber::header chain_grabber::MongoDatabase::FindHeaderByMerkle(std::string hash) {
    mongocxx::database db = client["gigamonkey"];
    mongocxx::collection coll = db["headers"];
    bsoncxx::stdx::optional<bsoncxx::document::value> maybe_result =
            coll.find_one(document{} << "merkleRoot" << hash << finalize);
    if(maybe_result) {
        return documentToStruct(maybe_result->view());
    }
}

chain_grabber::header chain_grabber::MongoDatabase::FindHeaderByHash(std::string hash) {
    mongocxx::database db = client["gigamonkey"];
    mongocxx::collection coll = db["headers"];
    bsoncxx::stdx::optional<bsoncxx::document::value> maybe_result =
            coll.find_one(document{} << "hash" << hash << finalize);
    if(maybe_result) {
        return documentToStruct(maybe_result->view());
    }
}

chain_grabber::header chain_grabber::MongoDatabase::documentToStruct(bsoncxx::document::view view) {
    header header;
    header.Nonce=view["nonce"].get_utf8().value.to_string();
    header.Target=view["target"].get_utf8().value.to_string();
    header.Timestamp=view["timestamp"].get_int64().value;
    header.MerkleRoot=view["merkleRoot"].get_utf8().value.to_string();
    header.Previous=view["previous"].get_utf8().value.to_string();
    header.Hash=view["hash"].get_utf8().value.to_string();
    header.Height=view["height"].get_int32().value;
    header.Version=view["version"].get_int32().value;
    return header;
}

void chain_grabber::MongoDatabase::connect() {
    client = {mongocxx::uri{config->getString("connectionString")}};
}
