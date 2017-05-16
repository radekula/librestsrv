/*
 * logger.hpp
 * This file is part of librestsrv
 *
 * Copyright (C) 2017 Radosław Ulatowski <radekula@gmail.com>
 *
 */


#ifndef __LIBRESTSRV_LOGGER_HPP__
#define __LIBRESTSRV_LOGGER_HPP__


#include <iostream>




namespace rest {
namespace server {


typedef enum
{
    DEBUG = 0,
    NOTICE,
    WARNING,
    ERROR
} LOG_LEVELS;



class Logger
{
private:
    Logger();
    ~Logger();

public:
    static Logger& get();

public:
    void log(int log_level, std::string message);
};




}
}




#endif
