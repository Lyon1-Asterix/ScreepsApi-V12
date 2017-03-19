#include "Api-V12/Routers/Auth.hpp"

namespace V12 {

Auth::Auth (ModuleApi* pApi) :
    ScreepsApi::Module ( "auth", pApi )
{
    addRoute ( "steam-ticket", ScreepsApi::Web::RoutingMethod::HttpPost, false, "" );
    addRoute ( "me", ScreepsApi::Web::RoutingMethod::HttpGet, true, "" );
    /* modauth */
    addRoute ( "signin", ScreepsApi::Web::RoutingMethod::HttpPost, false, "" );
}

}
