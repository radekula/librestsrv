/*
 * server.hpp
 * This file is part of librestsrv
 *
 * Copyright (C) 2017 Radosław Ulatowski <radekula@gmail.com>
 *
 */


#ifndef __LIBRESTSRV_SERVER_HPP__
#define __LIBRESTSRV_SERVER_HPP__

//#include <sys/types.h>
//#include <sys/socket.h>
//#include <netdb.h> 

#include <netinet/in.h>




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

public:
    RestSrv();
    ~RestSrv();

public:
    bool set_addr_type(int type);
    int get_addr_type();

    bool set_port(unsigned int port);
    unsigned int get_port();

    bool set_max_wait_connections(unsigned int connections);
    unsigned int get_max_wait_connections();

public:
    void run();
};




}
}




#endif
