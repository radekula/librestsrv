/*
 * server.hpp
 * This file is part of librestsrv
 *
 * Copyright (C) 2017 Radosław Ulatowski <radekula@gmail.com>
 *
 */


#ifndef __LIBRESTSRV_SERVER_HPP__
#define __LIBRESTSRV_SERVER_HPP__

#include <netinet/in.h>
#include <vector>
#include <memory>
#include <functional>
#include "client.hpp"
#include "request.hpp"
#include "response.hpp"



namespace rest {
namespace server {




class RestSrv
{
private:
    bool m_is_running;

private:
    int m_address_type;
    int m_listen_port;
    unsigned int m_max_wait_connections;

private:
    int m_listen_socket;
    sockaddr_in m_listen_address;
    std::function<void(rest::server::RestRequest&, rest::server::RestResponse&)> m_handler_fun;

private:
    std::vector<std::shared_ptr<RestClient>> m_clients;

private:
    std::string m_server_name;

public:
    std::string format_response(RestResponse &response);
    std::string http_code_to_string(unsigned int code);

public:
    RestSrv();
    RestSrv(std::function<void(rest::server::RestRequest&, rest::server::RestResponse&)> fun);
    ~RestSrv();

public:
    bool set_addr_type(int type);
    int get_addr_type();

    bool set_port(unsigned int port);
    unsigned int get_port();

    bool set_max_wait_connections(unsigned int connections);
    unsigned int get_max_wait_connections();

    bool set_server_name(std::string server_name);
    std::string get_server_name();

public:
    void register_function(std::function<void(rest::server::RestRequest&, rest::server::RestResponse&)> fun);

public:
    void run();
};




}
}




#endif
