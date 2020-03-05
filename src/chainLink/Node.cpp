// Copyright (c) 2019 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include "chainLink/Node.h"
#include "chainLink/messages/MessageHeader.h"
namespace chain_link {


    void Node::start() {
        boost::array<messages::MessageHeader,1> buf{};
        boost::asio::async_read(socket_,boost::asio::buffer(buf),boost::bind(&Node::handle_header,this,buf,boost::asio::placeholders::error));
    }

    void Node::handle_header(boost::array<messages::MessageHeader, 1> buf, const boost::system::error_code &error) {
        std::cout << buf[0] << std::endl;
    }

    Node::pointer Node::create(boost::asio::io_context &io_context, bool server) {
        return pointer(new Node(io_context,server));
    }
}
