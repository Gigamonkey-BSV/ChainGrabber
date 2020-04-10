#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <chainLink/Constants.h>
#include "chainLink/Node.h"
using boost::asio::ip::tcp;


int main()
{
    chain_link::Config::SetTestNet();
    boost::asio::io_context io_context;
    tcp::resolver resolver(io_context);
    tcp::resolver::results_type endpoints =
            resolver.resolve("157.230.96.95", chain_link::Config::getConfig().GetPort());
    chain_link::Node::pointer node=chain_link::Node::create(io_context);
    boost::asio::connect(node->socket(), endpoints);
    node->start();
    io_context.run();



    return 0;
}