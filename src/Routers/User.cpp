#include "Api-V12/Routers/User.hpp"

namespace V12 {

User::User (ModuleApi* pApi) :
    ScreepsApi::Module ( "user", pApi )
{
    addRoute ( "world-start-room", ScreepsApi::Web::RoutingMethod::HttpGet, true, "" );
    addRoute ( "world-status", ScreepsApi::Web::RoutingMethod::HttpGet, true, "" );
    addRoute ( "branches", ScreepsApi::Web::RoutingMethod::HttpGet, true, "withCode: bool" );
    addRoute ( "code", ScreepsApi::Web::RoutingMethod::HttpGet, true, "branch: (.*)" );
    addRoute ( "respawn-prohibited-rooms", ScreepsApi::Web::RoutingMethod::HttpGet, true, "" );
    addRoute ( "memory", ScreepsApi::Web::RoutingMethod::HttpGet, true, "path: ..." );
    addRoute ( "memory-segment", ScreepsApi::Web::RoutingMethod::HttpGet, true, "segment: 0..99" );
    addRoute ( "find", ScreepsApi::Web::RoutingMethod::HttpGet, false, "username: ..., id: ..." );
    addRoute ( "stats", ScreepsApi::Web::RoutingMethod::HttpGet, false, "interval: d+" );
    addRoute ( "rooms", ScreepsApi::Web::RoutingMethod::HttpGet, false, "id: ..." );
    addRoute ( "overview", ScreepsApi::Web::RoutingMethod::HttpGet, true, "interval: d+, statName: ..." );
    addRoute ( "money-history", ScreepsApi::Web::RoutingMethod::HttpGet, true, "page: d+" );

    addRoute ( "code", ScreepsApi::Web::RoutingMethod::HttpPost, true, "branch: (.*), modules: [ ((.*): \".*\")+ ]" );
    addRoute ( "badge", ScreepsApi::Web::RoutingMethod::HttpPost, true, "badge: { type: d+, param: d+, flip: bool, color1: hexColor, color2: hexColor, color3: hexColor }" );
    addRoute ( "respawn", ScreepsApi::Web::RoutingMethod::HttpPost, true, "" );
    addRoute ( "set-active-branch", ScreepsApi::Web::RoutingMethod::HttpPost, true, "activeName: (activeWorld|activeSim), branch: (.*)" );
    addRoute ( "clone-branch", ScreepsApi::Web::RoutingMethod::HttpPost, true, "branch: (.*), defaultModules: bool, newName: (.*)" );
    addRoute ( "delete-branch", ScreepsApi::Web::RoutingMethod::HttpPost, true, "branch: (.*)" );
    addRoute ( "memory", ScreepsApi::Web::RoutingMethod::HttpPost, true, "path: (.*), value: ..." );
    addRoute ( "memory-segment", ScreepsApi::Web::RoutingMethod::HttpPost, true, "segment: 0..99, data: ..." );
    addRoute ( "console", ScreepsApi::Web::RoutingMethod::HttpPost, true, "expression: (.*)" );
    addRoute ( "notify-prefs", ScreepsApi::Web::RoutingMethod::HttpPost, true, "disabled: bool, disabledOnMessages: bool, sendOnline: bool, interval: [5,10,30,60,180,360,720,1440,4320],errorsInterval: [0,5,10,30,60,180,360,720,1440,4320,100000]" );
    addRoute ( "tutorial-done", ScreepsApi::Web::RoutingMethod::HttpPost, true, "" );
    addRoute ( "email", ScreepsApi::Web::RoutingMethod::HttpPost, true, "email: mailaddr" );
}

}
