#include "stdafx.h"
#include "Server.h"

using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

std::unique_ptr<Server> g_http;

void on_initialize(const string_t& address)
{
    // Build our listener's URI from the configured address and the hard-coded path "Server/Action"

    uri_builder uri(address);
    uri.append_path(U("smartpay/payment/"));

    auto addr = uri.to_uri().to_string();

    

	g_http = std::unique_ptr<Server>(new Server(addr));
	g_http->open().wait();
    
    ucout << utility::string_t(U("Listening for requests at: ")) << addr << std::endl;

    return;
}

void on_shutdown()
{
	g_http->close().wait();
    return;
}

int wmain(int argc, wchar_t *argv[])
{
    utility::string_t port = U("34568");
    if(argc == 2)
    {
        port = argv[1];
    }

    utility::string_t address = U("http://localhost:");
    address.append(port);

    on_initialize(address);
    std::cout << "Press ENTER to exit." << std::endl;

    std::string line;
    std::getline(std::cin, line);

    on_shutdown();
    return 0;
}