/*
 * response.cxx
 * This file is part of librestsrv
 *
 * Copyright (C) 2017 Radosław Ulatowski <radekula@gmail.com>
 *
 */


#include "response.hpp"



namespace rest {
namespace server {




RestResponse::RestResponse()
{
    m_content_type = "Content-Type: application/json";
};




RestResponse::RestResponse(unsigned int code, std::string message)
{
    m_content_type = "Content-Type: application/json";
    m_http_code = code;
    m_message = message;
};




RestResponse::~RestResponse()
{
};




void RestResponse::set_http_code(unsigned int code)
{
    m_http_code = code;
};




unsigned int RestResponse::get_http_code()
{
    return m_http_code;
};




void RestResponse::set_message(std::string message)
{
    m_message = message;
};




std::string RestResponse::get_message()
{
    return m_message;
};




void RestResponse::set_content_type(std::string content_type)
{
    m_content_type = content_type;
};




std::string RestResponse::get_content_type()
{
    return m_content_type;
};




}
}
