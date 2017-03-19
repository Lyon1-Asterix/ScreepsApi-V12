#include "Api-V12/Routers/Register.hpp"

namespace V12 {

Register::Register (ModuleApi* pApi) :
    ScreepsApi::Module ( "register", pApi )
{
    addRoute ( "check-username", ScreepsApi::Web::RoutingMethod::HttpGet, false, "username: ..." );
    addRoute ( "check-email", ScreepsApi::Web::RoutingMethod::HttpGet, false, "email: ..." );
    addRoute ( "set-username", ScreepsApi::Web::RoutingMethod::HttpPost, true, "username: ..., email: ..." );
}

}
