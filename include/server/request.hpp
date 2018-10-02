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
#include <map>
#include <sstream>
#include <json/json.h>


namespace rest {
namespace server {




class RestRequest
{
private:
    std::string m_message;

private:
    std::string m_method;
    std::string m_resource;
    Json::Value m_body;

    std::map<std::string, std::string> m_headers;
    std::map<std::string, std::string> m_params;

private:
    void parse_headers(std::istringstream &stream);
    void parse_body(std::istringstream &stream);
    void parse_resource();

public:
    RestRequest();
    ~RestRequest();

public:
    void append_data(void *data, size_t size);
    void parse();

public:
    std::string &method();
    std::string &resource();
    std::map<std::string, std::string> &headers();
    std::map<std::string, std::string> &params();
    Json::Value &body();
};




}
}




#endif
