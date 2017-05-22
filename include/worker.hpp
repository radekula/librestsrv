/*
 * worker.hpp
 * This file is part of librestsrv
 *
 * Copyright (C) 2017 Radosław Ulatowski <radekula@gmail.com>
 *
 */


#ifndef __LIBRESTSRV_WORKER_HPP__
#define __LIBRESTSRV_WORKER_HPP__

#include <functional>
#include "client.hpp"


namespace rest {
namespace server {




class Worker
{
private:
    rest::server::RestRequest m_request;
    rest::server::RestResponse m_response;

private:
    std::function<void(rest::server::RestRequest&, rest::server::RestResponse&)> m_handler_fun;
    bool m_is_running;

public:
    Worker(std::function<void(rest::server::RestRequest&, rest::server::RestResponse&)> fun);
    ~Worker();

public:
    void run(std::shared_ptr<RestClient>);

    bool is_running();
    void set_is_running(bool is_running);

    std::function<void(rest::server::RestRequest&, rest::server::RestResponse&)> get_handler_fun();
    rest::server::RestRequest& get_request();
    rest::server::RestResponse& get_response();

    void send_response();

private:
    static void _worker_fun(rest::server::Worker *worker);
};




}
}




#endif
