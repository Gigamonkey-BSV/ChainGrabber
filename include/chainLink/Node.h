// Copyright (c) 2019 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CHAIN_GRABBER_NODE_H
#define CHAIN_GRABBER_NODE_H
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <chainLink/messages/MessageHeader.h>
#include <chainLink/messages/BaseMessage.h>
#include "boost/asio.hpp"
using boost::asio::ip::tcp;
namespace chain_link {
class Node : public boost::enable_shared_from_this<Node> {
public:
    typedef boost::shared_ptr<Node> pointer;
    [[nodiscard]] static pointer create(boost::asio::io_context& io_context,bool server=false);
    [[nodiscard]] inline tcp::socket& socket()
    {
        return socket_;
    }
    void start();
private:

    explicit Node(boost::asio::io_context& io_context,bool server) : socket_(io_context),server_(server) {

    }
    void handle_header(messages::BaseMessage buf,const boost::system::error_code& error);
    boost::asio::streambuf request_;
    boost::asio::streambuf response_;
    tcp::socket socket_;
    bool server_;
};
}
#endif //CHAIN_GRABBER_NODE_H
