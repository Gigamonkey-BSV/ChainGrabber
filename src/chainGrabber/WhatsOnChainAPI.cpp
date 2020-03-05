// Copyright (c) 2020 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainGrabber/BitcoinHeader.h>
#include <chainGrabber/WhatsOnChainAPI.h>
#include <json.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
namespace net = boost::asio;        // from <boost/asio.hpp>
using tcp = net::ip::tcp;           // from <boost/asio/ip/tcp.hpp>

namespace chain_grabber {
    std::string WHATS_ON_API_BASE="/v1/bsv/main/";
    const char* WHATS_ON_HOST="api.whatsonchain.com";
    std::string WHATS_ON_INFO="chain/info";

    header WhatsOnChainAPI::GetBlockHeader(std::string hash) {
        return header();
    }

    std::string WhatsOnChainAPI::GetHeadBlockHash() {
        std::string retval="";
        net::io_context ioc;
        tcp::resolver resolver(ioc);
        beast::tcp_stream stream(ioc);


        std::string target=WHATS_ON_API_BASE+WHATS_ON_INFO;
        // Look up the domain name
        auto const results = resolver.resolve(WHATS_ON_HOST, "80");

        stream.connect(results);
        std::cout << target << std::endl;
        std::cout << WHATS_ON_HOST << std::endl;
        http::request<http::string_body> req{http::verb::get,target , 11};
        req.set(http::field::host, WHATS_ON_HOST);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
        // Send the HTTP request to the remote host
        http::write(stream, req);

        // This buffer is used for reading and must be persisted
        beast::flat_buffer buffer;

        // Declare a container to hold the response
        http::response<http::dynamic_body> res;

        // Receive the HTTP response
        http::read(stream, buffer, res);


        std::string stf = beast::buffers_to_string(res.body().data());
        std::cout << stf << std::endl;
        auto j=nlohmann::json::parse(stf);
        retval=j.is_structured();
        // Gracefully close the socket
        beast::error_code ec;
        stream.socket().shutdown(tcp::socket::shutdown_both, ec);

        // not_connected happens sometimes
        // so don't bother reporting it.
        //
        if(ec && ec != beast::errc::not_connected)
            throw beast::system_error{ec};

        return retval;
    }
}
