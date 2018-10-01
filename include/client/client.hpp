/*
 * client.hpp
 * This file is part of librestsrv
 *
 * Copyright (C) 2017 Radosław Ulatowski <radekula@gmail.com>
 *
 */


#ifndef __LIBRESTSRV_CLIENT_HPP__
#define __LIBRESTSRV_CLIENT_HPP__

#include <netinet/in.h>




namespace rest {
namespace server {




class RestClient
{
private:
    int m_listen_socket;
    sockaddr_in m_address;
    unsigned int m_address_size;

public:
    RestClient();
    ~RestClient();

public:
    bool set_socket(int socket);
    int get_socket();

    sockaddr_in* get_address();
    unsigned int* get_address_size();
};




}
}




#endif
