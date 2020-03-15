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
        messages::BaseMessage buf{};
        boost::asio::async_read(socket_,response_,boost::asio::transfer_exactly(24),boost::bind(&Node::handle_header,this,buf,boost::asio::placeholders::error));
    }

    void Node::handle_header(messages::BaseMessage buf, const boost::system::error_code &error) {
        std::vector<unsigned char> header;
        for(int i=0;i<24;i++)
            //header.push_back(response_.data().data());
            int p=0;
        auto itr=header.begin();
        buf.header=chain_link::messages::MessageHeader::Deserialize(itr);
        std::cout << buf.header << std::endl;
    }

    Node::pointer Node::create(boost::asio::io_context &io_context, bool server) {
        return pointer(new Node(io_context,server));
    }
}
