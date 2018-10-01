#include <exception>
#include <cstring>
#include <unistd.h>
#include "global.hpp"
#include "server.hpp"
#include "response.hpp"
#include "log/logger.hpp"



namespace rest {
namespace server {




RestSrv::RestSrv()
{
    m_is_running = false;

    m_listen_socket = 0;
    m_address_type = ADDR_IPV4;
    m_listen_port = 80;
    m_max_wait_connections = 0;
    m_handler_fun = nullptr;
};




RestSrv::RestSrv(std::function<void(rest::server::RestRequest&, rest::server::RestResponse&)> fun)
{
    m_is_running = false;

    m_listen_socket = 0;
    m_address_type = ADDR_IPV4;
    m_listen_port = 80;
    m_max_wait_connections = 0;
    m_handler_fun = fun;
}




RestSrv::~RestSrv()
{
    if(m_listen_socket)
        close(m_listen_socket);
};




bool RestSrv::set_addr_type(int type)
{
    if(m_is_running)
        return false;

    m_address_type = type;

    return true;
};




int RestSrv::get_addr_type()
{
    return m_address_type;
};




bool RestSrv::set_port(unsigned int port)
{
    if(m_is_running)
        return false;

    m_listen_port = port;

    return true;
};




unsigned int RestSrv::get_port()
{
    return m_listen_port;
};




bool RestSrv::set_max_wait_connections(unsigned int connections)
{
    if(m_max_wait_connections)
        return false;

    m_max_wait_connections = connections;

    return true;
};




unsigned int RestSrv::get_max_wait_connections()
{
    return m_max_wait_connections;
};




std::string RestSrv::http_code_to_string(unsigned int code)
{
    std::string out;

    switch(code)
    {
        case 200:
            out = "200 OK";
            break;
    }

    return out;
}





std::string RestSrv::format_response(RestResponse &response)
{
    std::string out;

    out = std::string("HTTP/1.1 ") + RestSrv::http_code_to_string(response.get_http_code()) + "\n"
          + "Date: Thu, 19 Feb 2009 12:27:04 GMT\n"
          + "Server: Apache/2.2.3\n"
          + "Last-Modified: Wed, 18 Jun 2003 16:05:58 GMT\n"
          + "ETag: \"56d-9989200-1132c580\"\n"
          + response.get_content_type() + "\n"
          + "Content-Length: " + std::to_string(response.get_message().size()) + "\n"
          + "Accept-Ranges: bytes\n"
          + "Connection: close\n"
          + "\n"
          + response.get_message();

    return out;
}



void RestSrv::register_function(std::function<void(rest::server::RestRequest&, rest::server::RestResponse&)> fun)
{
    m_handler_fun = fun;
};




void RestSrv::run()
{
    rest::log::Logger::get().log(rest::log::NOTICE, "Server started");
    try
    {
        m_is_running = true;

        m_listen_socket = socket(AF_INET, SOCK_STREAM, 0);

        if(m_listen_socket < 0)
        {
            rest::log::Logger::get().log(rest::log::ERROR , "Error creating socket");
            throw std::exception();
        }

        memset((char *) &m_listen_address, 0, sizeof(m_listen_address));
        m_listen_address.sin_family = m_address_type;
//TODO: defining addresses to listen to
        m_listen_address.sin_addr.s_addr = INADDR_ANY;
        m_listen_address.sin_port = htons(m_listen_port);

        if(bind(m_listen_socket, (struct sockaddr *) &m_listen_address, sizeof(m_listen_address)) < 0)
        {
            rest::log::Logger::get().log(rest::log::ERROR , "Error binding to socket");
            throw std::exception();
        }

        if(listen(m_listen_socket, m_max_wait_connections) < 0)
        {
            rest::log::Logger::get().log(rest::log::ERROR , "Error listen on socket");
            throw std::exception();
        }

        while(true)
        {
            std::shared_ptr<RestClient> new_client = std::make_shared<RestClient>();

            new_client->set_socket(accept(m_listen_socket, (struct sockaddr *) new_client->get_address(), new_client->get_address_size()));
            if(new_client->get_socket() < 0)
            {
                rest::log::Logger::get().log(rest::log::ERROR , "Error listen on socket");
                throw std::exception();
            }

            rest::log::Logger::get().log(rest::log::NOTICE, "New client connected");

            char buff[4096];
            recv(new_client->get_socket(), buff, sizeof(buff), 0);

            RestRequest request;
            RestResponse response;

            if(m_handler_fun)
            {
                rest::log::Logger::get().log(rest::log::NOTICE, "Running handler");
                m_handler_fun(request, response);
            }
            else
            {
                rest::log::Logger::get().log(rest::log::WARNING, "Handler function was not defined");
                response.set_http_code(200);
                response.set_message("test message");
            };

            auto server_response = format_response(response);

            rest::log::Logger::get().log(rest::log::NOTICE, "Sending responce");
            if(send(new_client->get_socket(), server_response.c_str(), server_response.size(), 0) < 0)
                throw std::exception();

        };
    } 
    catch(std::exception e) 
    {
        m_is_running = false;
        throw e;
    };

    m_is_running = false;
};




}
}
