#include "stdafx.h"
#include "messagetypes.h"
#include "Server.h"

using namespace std;
using namespace web; 
using namespace utility;
using namespace http;
using namespace web::http::experimental::listener;

Server::Server(utility::string_t url) : m_listener(url)
{
    m_listener.support(methods::GET, std::bind(&Server::handle_get, this, std::placeholders::_1));
    m_listener.support(methods::PUT, std::bind(&Server::handle_put, this, std::placeholders::_1));
    m_listener.support(methods::POST, std::bind(&Server::handle_post, this, std::placeholders::_1));
    m_listener.support(methods::DEL, std::bind(&Server::handle_delete, this, std::placeholders::_1));
  
}

void Server::handle_get(http_request message)
{
    ucout <<  message.to_string() << endl;
    message.reply(status_codes::OK,"handle_get");
	//TODO
};

void Server::handle_post(http_request message)
{
    ucout <<  message.to_string() << endl;
	message.reply(status_codes::OK, "handle_post");
	//TODO
};

void Server::handle_delete(http_request message)
{
	ucout << message.to_string() << endl;
	message.reply(status_codes::OK, "handle_delete");
	//TODO
}

void Server::handle_put(http_request message)
{
	ucout << message.to_string() << endl;

	auto paths = uri::split_path(uri::decode(message.relative_uri().path()));
	auto query = uri::split_query(uri::decode(message.relative_uri().query()));
	auto queryItr = query.find(U("request"));
	utility::string_t request = queryItr->second;
	ucout <<"Request"<< request << endl;
	//TODO

	message.reply(status_codes::OK);
};
