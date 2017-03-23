#include "Api-V12/Api.hpp"

#include "Api-V12/Routers/Client.hpp"

#include "Api-V12/Data.hpp"

namespace V12 {

nlohmann::json to_json (ScreepsApi::Reply reply) {
    return reply.data._json;
}

Api::Api(std::shared_ptr<ScreepsApi::Web::Client> pClient,std::shared_ptr<ScreepsApi::Web::Socket> pSocket) :
    ScreepsApi::Api ( pClient,pSocket ),
    m_client ( this ),
    m_initialized ( false )
{
    Data::Get().m_connected = false;
    Data::Get().m_workingDirectory = ".";
}

/*
*/

bool Api::Signin ( std::string email, std::string password )
{
    m_initialized = false;
    nlohmann::json content, reply;
    content["email"] = email;
    content["password"] = password;
    auto tmp = m_client["api"]["auth"].route ( "signin", content.dump () );
    auto auth = reply = to_json ( tmp );
    if ( reply.find ( "ok" ) == reply.end () ) return false;
    if ( reply["ok"].get<int>() != 1) return false;
    setToken (reply["token"].get<std::string>());
    /*
    auto user = reply = to_json ( m_client["api"]["auth"].route ( "me" ) );
    if ( reply.find ( "ok" ) == reply.end () ) return false;
    if ( reply["ok"].get<int>() != 1) return false;
    auto room = reply = to_json ( m_client["api"]["user"].route ( "world-start-room" ) );
    if ( reply.find ( "ok" ) == reply.end () ) return false;
    if ( reply["ok"].get<int>() != 1) return false;
    auto status = reply = to_json ( m_client["api"]["user"].route ( "world-status" ) );
    if ( reply.find ( "ok" ) == reply.end () ) return false;
    if ( reply["ok"].get<int>() != 1) return false;
    auto branches = reply = to_json ( m_client["api"]["user"].route ( "branches","{\"withCode\":false}" ) );
    if ( reply.find ( "ok" ) == reply.end () ) return false;
    if ( reply["ok"].get<int>() != 1) return false;
    Data::Get().m_connected = true;
    */
    m_initialized = true;
    return true;
}

bool Api::PushCode ( std::string branch )
{
    nlohmann::json content, reply;
    Data::Get().m_code.m_branches[branch].ToJSON ( content );
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
    //Data::Get().setUser ( user );
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
    //Data::Get ().setRoom ( reply["terrain"][0] );
    return reply["terrain"][0];
}

nlohmann::json Api::PullCode ( std::string branch )
{
    nlohmann::json content, reply, out;
    content["branch"] = branch;
    reply = to_json ( m_client["api"]["user"].route ( "code", content.dump (), ScreepsApi::Web::RoutingMethod::HttpGet ) );
    if ( reply.find ( "ok" ) == reply.end () ) return out;
    if ( reply["ok"].get<int>() != 1) return out;
    //CodeBranch c; c.FromJSON ( reply );
    //Data::Get().m_code.m_branches[c.m_branch] = c;
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
