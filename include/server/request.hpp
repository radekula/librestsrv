/*
 * request.hpp
 * This file is part of librestsrv
 *
 * Copyright (C) 2017 Radosław Ulatowski <radekula@gmail.com>
 *
 */


#ifndef __LIBRESTSRV_REQUEST_HPP__
#define __LIBRESTSRV_REQUEST_HPP__



#include <string>



namespace rest {
namespace server {




class RestRequest
{
private:
    std::string m_url;
    std::string m_headers;
    std::string m_body;

public:
    RestRequest();
    ~RestRequest();

public:
    void set_url(std::string url);
    void append_data(void *data, size_t size);

public:
    std::string get_url();
    std::string get_headers();
    std::string get_body();
};




}
}




#endif
