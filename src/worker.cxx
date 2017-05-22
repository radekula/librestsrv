#include "worker.hpp"
#include "logger.hpp"



namespace rest {
namespace server {




Worker::Worker(std::function<void(rest::server::RestRequest&, rest::server::RestResponse&)> fun)
{
    m_is_running = false;
    m_handler_fun = fun;
};




Worker::~Worker()
{
};




void Worker::run(std::shared_ptr<rest::server::RestClient>)
{
    get_request();
    std::thread t(&_worker_fun, this);
};




bool Worker::is_running()
{
    return m_is_running;
};




void Worker::set_is_running(bool is_running)
{
    m_is_running = is_running;
};




std::function<void(rest::server::RestRequest&, rest::server::RestResponse&)> Worker::get_handler_fun()
{
    return m_handler_fun;
};




rest::server::RestRequest& Worker::get_request()
{
    return m_request;
};




rest::server::RestResponse& Worker::get_response()
{
    return m_response;
};




void Worker::send_response()
{
};




static void Worker::_worker_fun(rest::server::Worker *worker)
{
    worker->set_is_running(true);
    
    auto fun = worker->get_handler_fun();
    fun(worker->get_request(), worker->get_response());

    worker->send_response();

    worker->set_is_running(false);
};




}
}
