#include "Api-V12/Routers/Game.hpp"

namespace V12 {

Game::Game (ModuleApi* pApi) :
    ScreepsApi::Module ( "game", pApi )
{
    addRoute ( "time",          ScreepsApi::Web::RoutingMethod::HttpGet, false, "" );
    addRoute ( "room-terrain",  ScreepsApi::Web::RoutingMethod::HttpGet, false, "room: WdNd, encoded: (true|false)" );
    addRoute ( "room-status",   ScreepsApi::Web::RoutingMethod::HttpGet, false, "room: WdNd" );
    addRoute ( "room-overview", ScreepsApi::Web::RoutingMethod::HttpGet, true,  "room: WdNd" );
    addRoute ( "world-size",    ScreepsApi::Web::RoutingMethod::HttpGet, false, "" );

    addRoute ( "map-stats", ScreepsApi::Web::RoutingMethod::HttpPost, true, "rooms: [ (WdNd)+ ], statName: (.*?)(d+)" );
    addRoute ( "gen-unique-object-name", ScreepsApi::Web::RoutingMethod::HttpPost, true, "type: (.*)" );
    addRoute ( "check-unique-object-name", ScreepsApi::Web::RoutingMethod::HttpPost, true, "type: (.*), name: (.*)" );
    addRoute ( "place-spawn", ScreepsApi::Web::RoutingMethod::HttpPost, true, "room: WdNd, name: (.*), x: d+, y: d+" );
    addRoute ( "create-flag", ScreepsApi::Web::RoutingMethod::HttpPost, true, "room: WdNd, name: (.*), x: d+, y: d+, color: ..., secondaryColor: ..." );
    addRoute ( "gen-unique-flag-name", ScreepsApi::Web::RoutingMethod::HttpPost, true, "" );
    addRoute ( "check-unique-flag-name", ScreepsApi::Web::RoutingMethod::HttpPost, true, "name: (.*)" );
    addRoute ( "change-flag-color", ScreepsApi::Web::RoutingMethod::HttpPost, true, "room: WdNd, name: (.*), color: ..., secondaryColor: ..." );
    addRoute ( "remove-flag", ScreepsApi::Web::RoutingMethod::HttpPost, true, "room: WdNd, name: (.*)" );
    addRoute ( "add-object-intent", ScreepsApi::Web::RoutingMethod::HttpPost, true, "room: WdNd, name: (.*), intent: ..., _id: ..." );
    addRoute ( "create-construction", ScreepsApi::Web::RoutingMethod::HttpPost, true, "room: WdNd, name: (.*), structureType: ..., x: d+, y: d+" );
    addRoute ( "set-notify-when-attacked", ScreepsApi::Web::RoutingMethod::HttpPost, true, "_id: ..., enabled: (true|false)" );
    addRoute ( "create-invader", ScreepsApi::Web::RoutingMethod::HttpPost, true, "room: WdNd, size: d+, type: ..., x: d+, y: d+" );
    addRoute ( "remove-invader", ScreepsApi::Web::RoutingMethod::HttpPost, true, "_id: ..." );
}

}
