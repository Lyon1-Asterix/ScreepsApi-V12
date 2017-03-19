#include "Api-V12/Routers/Api.hpp"

#include "Api-V12/Routers/Auth.hpp"
#include "Api-V12/Routers/Register.hpp"
#include "Api-V12/Routers/Game.hpp"
#include "Api-V12/Routers/User.hpp"

namespace V12 {

ModuleApi::ModuleApi (Client* pClient) :
    ScreepsApi::Module ( "api", pClient )
{
    addRoute ( "version", ScreepsApi::Web::RoutingMethod::HttpGet, false, "" );
    new Auth( this );
    new Register( this );
    new Game( this );
    new User( this );
}

}
