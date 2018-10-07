/*
 * client.cxx
 * This file is part of librestsrv
 *
 * Copyright (C) 2017 Radosław Ulatowski <radekula@gmail.com>
 *
 */


#include <netinet/in.h>
#include <unistd.h>
#include "client.hpp"



namespace rest {
namespace server {




RestClient::RestClient()
{
    m_listen_socket = 0;
    m_address_size = sizeof(m_address);
};




RestClient::~RestClient()
{
    if(m_listen_socket)
        close(m_listen_socket);
};




bool RestClient::set_socket(int socket)
{
    m_listen_socket = socket;
    return true;
};




int RestClient::get_socket()
{
    return m_listen_socket;
};




sockaddr_in* RestClient::get_address()
{
    return &m_address;
};




unsigned int* RestClient::get_address_size()
{
    return &m_address_size;
};



}
}


