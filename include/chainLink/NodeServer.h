// Copyright (c) 2019 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CHAIN_GRABBER_NODESERVER_H
#define CHAIN_GRABBER_NODESERVER_H

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
using boost::asio::ip::tcp;

namespace chain_link {
    class NodeServer {
    public:
        explicit NodeServer(boost::asio::io_context& io_context):
        io_context_(io_context),acceptor_(io_context,tcp::endpoint(tcp::v6(),8333)){
            start_accept();
        }

    private:
        void start_accept();
        boost::asio::io_context& io_context_;
        tcp::acceptor acceptor_;
        std::vector<Node::pointer> connections;
    };
}
#endif //CHAIN_GRABBER_NODESERVER_H
