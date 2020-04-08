//
// timer.cpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2019 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <chainLink/Constants.h>
#include "chainLink/Node.h"
using boost::asio::ip::tcp;

char* ip="157.230.96.95";

int main()
{
    chain_link::Config::SetTestNet();
    boost::asio::io_context io_context;
    tcp::resolver resolver(io_context);
    tcp::resolver::results_type endpoints =
            resolver.resolve("157.230.96.95", "18333");
    chain_link::Node::pointer node=chain_link::Node::create(io_context);
    boost::asio::connect(node->socket(), endpoints);
    node->start();
    io_context.run();



    return 0;
}