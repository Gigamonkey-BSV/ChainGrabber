// Copyright (c) 2019 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include "chainLink/Node.h"
#include "chainLink/Version.h"
#include "chainLink/messages/MessageHeader.h"
#include "chainLink/messages/VersionPayload.h"
#include "chainLink/messages/RejectPayload.h"
namespace chain_link {


    void Node::start() {
        messages::BaseMessage buf{};
        chain_link::messages::Version version1;
        version1.services=1 << 0;
        version1.addr_from.setIP(0,0,0,0);
        version1.addr_from.port=0;
        version1.version=CURRENT_VERSION;
        version1.addr_to.port=socket_.remote_endpoint().port();
        version1.addr_to.setIP(157,230,96,95);
        version1.user_agent="/chainGrabber:0:00";
        messages::BaseMessage send;
        std::shared_ptr<chain_link::messages::Payload> payload=std::make_shared<chain_link::messages::Version>(version1);
        send=chain_link::messages::BaseMessage::MakeMessage("version",payload);
        std::vector<unsigned char> output=send.Serialize();
        boost::asio::write(socket_,boost::asio::buffer(output));
        boost::asio::async_read(socket_,response_,boost::asio::transfer_exactly(24),boost::bind(&Node::handle_header,this,buf,boost::asio::placeholders::error));
    }

    void Node::handle_header(messages::BaseMessage buf, const boost::system::error_code &error) {
        std::vector<unsigned char> header;
        auto* output = (unsigned char*)malloc(response_.size());
        memcpy(output, boost::asio::buffer_cast<const void*>(response_.data()), response_.size());
        header=std::vector<unsigned char>(output,output+24);
        //if(!=24) {
        //    boost::asio::async_read(socket_,response_,boost::asio::transfer_exactly(24),boost::bind(&Node::handle_header,this,buf,boost::asio::placeholders::error));
        //    return;
        //}
        auto itr=header.begin();
        buf.header=chain_link::messages::MessageHeader::Deserialize(itr);
        response_.consume(response_.size());
        std::cout << buf.header << std::endl;
        boost::asio::async_read(socket_,response_,boost::asio::transfer_exactly(buf.header.PayloadSize),boost::bind(&Node::handle_payload,this,buf,boost::asio::placeholders::error));
    }

    Node::pointer Node::create(boost::asio::io_context &io_context, bool server) {
        return pointer(new Node(io_context,server));
    }

    void Node::handle_payload(messages::BaseMessage buf, const boost::system::error_code &error) {
        std::vector<unsigned char> header;
        auto* output = (unsigned char*)malloc(response_.size());
        memcpy(output, boost::asio::buffer_cast<const void*>(response_.data()), response_.size());
        header=std::vector<unsigned char>(output,output+response_.size());

        auto itr=header.begin();
        std::string tmp=buf.header.CommandName;
        if(tmp=="version") {
            auto version1=std::shared_ptr<chain_link::messages::Version>(chain_link::messages::Version::Deserialize(itr));
            buf.setPayload(version1);
        } else if(tmp=="reject") {
            auto tmp2=header.end();
            auto reject1=std::make_shared<chain_link::messages::RejectPayload>(chain_link::messages::RejectPayload::Deserialize(itr,tmp2));
            buf.setPayload(reject1);
        } else
        {
            std::cout << "Unknown Command name: " + tmp;
        }
        std::cout << buf.payload;
    }
}
