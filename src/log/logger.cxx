/*
 * logger.cxx
 * This file is part of librestsrv
 *
 * Copyright (C) 2017 Radosław Ulatowski <radekula@gmail.com>
 *
 */

#include "logger.hpp"




namespace rest {
namespace log {




Logger::Logger()
{
};




Logger::~Logger()
{
};




Logger& Logger::get()
{
    static Logger log;

    return log;
};




int Logger::log(int log_level, std::string message)
{
    std::cout << message << std::endl;

    return 0;
};




}
}



