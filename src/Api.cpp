#include "Api-V12/Api.hpp"

#include "Api-V12/Routers/Client.hpp"

namespace V12 {

nlohmann::json to_json (ScreepsApi::Reply reply) {
    return reply.data._json;
}

Api::Api(std::shared_ptr<ScreepsApi::Web::Client> pClient,
        std::shared_ptr<ScreepsApi::Web::Socket> pSocket) :
    ScreepsApi::Api ( pClient,pSocket ),
    m_client ( this ),
    m_initialized ( false )
{
}

/*
*/

bool Api::Signin ( std::string email, std::string password )
{
    m_initialized = false;
    nlohmann::json content, reply;
    content["email"] = email;
    content["password"] = password;
    reply = to_json ( m_client["api"]["auth"].route ( "signin", content.dump () ) );
    if ( reply.find ( "ok" ) == reply.end () ) return false;
    if ( reply["ok"].get<int>() != 1) return false;
    setToken (reply["token"].get<std::string>());
    m_initialized = true;
    return true;
}

bool Api::PushCode ( std::string branch, std::map < std::string, std::string > modules )
{
    nlohmann::json content, reply;
    content["branch"] = branch;
    for (auto it : modules ) {
        std::string name = it.first;
        std::string code = it.second;
        content [ "modules" ] [ name ] = code;
    }
    reply = to_json ( m_client["api"]["user"].route ( "code", content.dump (), ScreepsApi::Web::RoutingMethod::HttpPost ) );
    if ( reply.find ( "ok" ) == reply.end () ) return false;
    if ( reply["ok"].get<int>() != 1) return false;
    return true;
}

bool Api::Console ( std::string command )
{
    nlohmann::json args;
    args["expression"] = command;
    nlohmann::json reply = to_json ( m_client["api"]["user"].route ( "console", args.dump () ) );
    return true;
}

bool Api::AddSpawn ( std::string name, std::string x, std::string y )
{
    nlohmann::json args;
    args["room"] = name;
    args["x"] = x;
    args["y"] = y;
    nlohmann::json reply = to_json ( m_client["api"]["game"].route ( "place-spawn", args.dump () ) );
    if ( reply.find ( "ok" ) == reply.end () ) return false;
    if ( reply["ok"].get<int>() != 1 ) return false;
    return true;
}

nlohmann::json Api::User ()
{
    nlohmann::json out = {};
    nlohmann::json reply = to_json ( m_client["api"]["auth"].route ( "me" ) );
    if ( reply.find ( "ok" ) == reply.end () ) return out;
    if ( reply["ok"].get<int>() != 1 ) return out;
    return reply;
}

nlohmann::json Api::Room ( std::string name )
{
    nlohmann::json args, out = {};
    args["room"] = name;
    args["encoded"] = false;
    nlohmann::json reply = to_json ( m_client["api"]["game"].route ( "room-terrain", args.dump () ) );
    if ( reply.find ( "ok" ) == reply.end () ) return out;
    if ( reply["ok"].get<int>() != 1 ) return out;
    return reply["terrain"][0];
}

nlohmann::json Api::PullCode ( std::string branch )
{
    nlohmann::json content, reply, out;
    content["branch"] = branch;
    reply = to_json ( m_client["api"]["user"].route ( "code", content.dump (), ScreepsApi::Web::RoutingMethod::HttpGet ) );
    if ( reply.find ( "ok" ) == reply.end () ) return out;
    if ( reply["ok"].get<int>() != 1) return out;
    return reply;
}

void Api::ConsoleListener (std::function<void(nlohmann::json)> callback)
{
}

void Api::RoomListener (std::string room, std::function<void(nlohmann::json)> callback)
{
}

void Api::WorldListener (std::function<void(nlohmann::json)> callback)
{
}

void Api::UserListener (std::function<void(nlohmann::json)> callback)
{
}

}
