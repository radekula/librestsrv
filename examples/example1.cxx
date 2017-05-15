#include <restsrv.hpp>
#include <memory>



int main()
{
    auto srv = std::make_unique<rest::server::RestSrv>();
    srv->set_port(8080);

    srv->run();
};

