#include <restsrv.hpp>
#include <memory>



void request_handler(rest::server::RestRequest &request, rest::server::RestResponse &response)
{
    if(request.resource() != "/screen")
    {
        response.set_http_code(404);
        return;
    };

    if(request.method() != "POST")
    {
        response.set_http_code(405);
        return;
    };

    std::cout << "Method: " << request.method() << std::endl;
    std::cout << "Resource: " << request.resource() << std::endl;
    for(auto a : request.headers())
        std::cout << "Header: " << a.first << ":" << a.second << std::endl;

    std::cout << "Request body: \n" << request.body() << std::endl;
    response.set_http_code(200);
    response.set_message("example1\n");
};





int main()
{
    rest::server::RestSrv srv(request_handler);
    srv.set_port(8081);
    srv.run();
};

