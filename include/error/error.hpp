/*
 * logger.hpp
 * This file is part of librestsrv
 *
 * Copyright (C) 2018 Radosław Ulatowski <radekula@gmail.com>
 *
 */


#ifndef __LIBRESTSRV_ERROR_HPP__
#define __LIBRESTSRV_ERROR_HPP__


#include <iostream>



namespace rest {
namespace error {



class Error
{
private:
    int m_code;
    std::string m_message;

public:
    Error();
    Error(int code, std::string message);

public:
    ~Error();

public:
    void set_code(int code);
    void get_message(std::string message);

    int get_code();
    std::string get_message();
};


}
}
