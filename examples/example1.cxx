#include <restsrv.hpp>
#include <memory>



void request_handler(rest::server::RestRequest &request, rest::server::RestResponse &response)
{
    std::cout << "Request body: \n" << request.get_body() << std::endl;
    response.set_http_code(200);
    response.set_message("example1\n");
};





int main()
{
    rest::server::RestSrv srv(request_handler);
    srv.set_port(8081);
    srv.run();
};

