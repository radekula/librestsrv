#include <exception>
#include <cstring>
#include <unistd.h>
#include "global.hpp"
#include "server.hpp"


//TODO remove
#include <iostream>


namespace rest {
namespace server {


RestSrv::RestSrv()
{
    m_is_running = false;

    m_listen_socket = 0;
    m_address_type = ADDR_IPV4;
    m_listen_port = 80;
    m_max_wait_connections = 0;
};




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
};




unsigned int RestSrv::get_max_wait_connections()
{
    return m_max_wait_connections;
};




void RestSrv::run()
{
    m_listen_socket = socket(AF_INET, SOCK_STREAM, 0);

    if(m_listen_socket < 0)
        throw std::exception();

    memset((char *) &m_listen_address, 0, sizeof(m_listen_address));
    m_listen_address.sin_family = m_address_type;
//TODO: defining addresses to listen to
    m_listen_address.sin_addr.s_addr = INADDR_ANY;
    m_listen_address.sin_port = htons(m_listen_port);

    if(bind(m_listen_socket, (struct sockaddr *) &m_listen_address, sizeof(m_listen_address)) < 0)
        throw std::exception();

    if(listen(m_listen_socket, m_max_wait_connections) < 0)
        throw std::exception();

    while(true)
    {
        sockaddr_in client_address;
        socklen_t m_clilen = sizeof(client_address);

        auto client_socket = accept(m_listen_socket, (struct sockaddr *) &client_address, &m_clilen);
        if(client_socket < 0) 
            throw std::exception();

            char buff[4096];
            if(recv(client_socket, buff, sizeof(buff), 0) > 0)
            {
                std::cout << buff << std::endl;

                char reply[] = 
                "HTTP/1.1 200 OK\n"
                "Date: Thu, 19 Feb 2009 12:27:04 GMT\n"
                "Server: Apache/2.2.3\n"
                "Last-Modified: Wed, 18 Jun 2003 16:05:58 GMT\n"
                "ETag: \"56d-9989200-1132c580\"\n"
                "Content-Type: text/html\n"
                "Content-Length: 15\n"
                "Accept-Ranges: bytes\n"
                "Connection: close\n"
                "\n"
                "test response\n";

                send(client_socket, reply, sizeof(reply), 0);
/*                Json::Value data;
                
                Json::Reader reader;
                if(!reader.parse(buff, data))
                {
                    std::cout << "Błąd akceptowania" << std::endl;
                    continue;
                }

                if(data.isMember("decision"))
                {
                    real = data;
                    if(verify())
                        std::cout << "Otrzymałem zweryfikowaną decyzję." << std::endl;
                    else
                        std::cout << "Otrzymałem podejrzaną decyzję!" << std::endl;
                }
                else
                    secret = data;*/
            }
    };
};




}
}
