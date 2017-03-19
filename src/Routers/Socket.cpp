#include "Api-V12/Routers/Socket.hpp"

namespace V12 {

Socket::Socket (Client* pClient) :
    ScreepsApi::Module ( "socket", pClient )
{
    addRoute ( "info", ScreepsApi::Web::RoutingMethod::HttpGet, false, "" );
}

}
