/*
 * request.cxx
 * This file is part of librestsrv
 *
 * Copyright (C) 2017 Radosław Ulatowski <radekula@gmail.com>
 *
 */


#include "request.hpp"
#include <string.h>
#include <string>
#include "log/logger.hpp"




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

    m_message.append(buff);
};



void RestRequest::parse_headers(std::istringstream &data_stream)
{
    std::string line;

    // every header line is composed with name and value
    while(std::getline(data_stream, line))
    {
        // end of headers
        if(line.size() < 3)
            break;

        auto delimiter = line.find(":");
        if(delimiter == std::string::npos)
        {
            m_headers[line] = "";
            continue;
        };

        auto name = line.substr(0, delimiter);

        delimiter++;
        while(line[delimiter] == ' ')
            delimiter++;

        auto value = line.substr(delimiter);
        m_headers[name] = value; 
    }
};




void RestRequest::parse_body(std::istringstream &data_stream)
{
 /*   std::string line;
    std::string body_raw;

    while(std::getline(data_stream, line))
        body_raw.append(line + "\n");*/

    std::string errs;
    Json::CharReaderBuilder builder;
    builder["collectComments"] = false;

    auto success = Json::parseFromStream(builder, data_stream, &m_body, &errs);
rest::log::Logger::get().log(rest::log::DEBUG, errs);
    if(!success)
        rest::log::Logger::get().log(rest::log::DEBUG, "Error parsing body");

};




void RestRequest::parse_resource()
{
};




void RestRequest::parse()
{
    if(m_message.size() < 1)
        return;

    std::istringstream data_stream(m_message);

    // parse header first
    std::string line;

    // first line must contain method, resource and protocol
    std::getline(data_stream, line);
    std::istringstream req(line);
    req >> m_method;
    req >> m_resource;
    //req >> m_protocol;  // ignore protocol - TODO: propper protocol handling

    parse_headers(data_stream);
    parse_body(data_stream);
    parse_resource();

    // no need for original message anymore
    m_message.clear();
};



std::string &RestRequest::method()
{
    return m_method;
};



std::string &RestRequest::resource()
{
    return m_resource;
};




std::map<std::string, std::string> &RestRequest::headers()
{
    return m_headers;
};




std::map<std::string, std::string> &RestRequest::params()
{
    return m_params;
};




Json::Value &RestRequest::body()
{
    return m_body;
};


}
}
