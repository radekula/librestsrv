/*
 * response.hpp
 * This file is part of librestsrv
 *
 * Copyright (C) 2017 Radosław Ulatowski <radekula@gmail.com>
 *
 */


#ifndef __LIBRESTSRV_RESPONSE_HPP__
#define __LIBRESTSRV_RESPONSE_HPP__

#include <netinet/in.h>
#include <string>



namespace rest {
namespace server {




class RestResponse
{
private:
    unsigned int m_http_code;
    std::string m_message;
    std::string m_content_type;

public:
    RestResponse();
    RestResponse(unsigned int code, std::string message);
    ~RestResponse();

public:
    void set_http_code(unsigned int code);
    unsigned int get_http_code();

    void set_message(std::string message);
    std::string get_message();

    void set_content_type(std::string content_type);
    std::string get_content_type();
};




}
}




#endif
