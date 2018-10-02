/*
 * request.cxx
 * This file is part of librestsrv
 *
 * Copyright (C) 2017 Radosław Ulatowski <radekula@gmail.com>
 *
 */


#include "request.hpp"
#include <string.h>


namespace rest {
namespace server {




RestRequest::RestRequest()
{
};




RestRequest::~RestRequest()
{
};




void RestRequest::append_data(void *data, size_t size)
{
    char *buff = new char[size + 1];
    memcpy(buff, data, size);
    buff[size] = 0;
    
    m_body.append(buff);
};




void RestRequest::set_url(std::string url)
{
    m_url = url;
};





std::string RestRequest::get_url()
{
    return m_url;
};




std::string RestRequest::get_headers()
{
    return m_headers;
};




std::string RestRequest::get_body()
{
    return m_body;
};


}
}
