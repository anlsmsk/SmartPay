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
    m_listener.support(methods::GET, std::bind((&Server::handle_get), this, std::placeholders::_1));
    m_listener.support(methods::PUT, std::bind(&Server::handle_put, this, std::placeholders::_1));
    m_listener.support(methods::POST, std::bind(&Server::handle_post, this, std::placeholders::_1));
    m_listener.support(methods::DEL, std::bind(&Server::handle_delete, this, std::placeholders::_1));
  
}

 void Server::handle_get(http_request message)
{
    ucout <<  message.to_string() << endl;

    auto path = uri::split_path(uri::decode(message.relative_uri().path()));
    auto query = uri::split_query(uri::decode(message.relative_uri().query()));
    auto res = query.find(U("request"));

    ucout << path[0] << endl;
    ucout << path[1] << endl;
    ucout << path[2] << endl;


    if (!path.empty() &&
        path[0] == U("cardType") &&
        path[1] == U("transactionType") &&
        path[2] == U("id")) {
        message.
            extract_json().
            then([=](json::value request) {
            try {

                Payment payment;
             
                payment.cardType = U("Visa");
                payment.transactionType = U("Credit");

                auto response = json::value::object();
                response[U("id")] = json::value::string(U("0.1.1"));
                response[U("message")] = json::value::string(U("succesful took!"));

                message.reply(status_codes::OK, response);
            }
  
            catch (json::json_exception & e) {
                message.reply(status_codes::BadRequest);
            }
                });
    }

    message.reply(status_codes::BadRequest, "Wrong Request");

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
