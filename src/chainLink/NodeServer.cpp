// Copyright (c) 2019 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainLink/Node.h>
#include "chainLink/NodeServer.h"
namespace chain_link {

    void NodeServer::start_accept() {
        Node::pointer new_connection = Node::create(io_context_);
        connections.push_back(new_connection);

    }
}
