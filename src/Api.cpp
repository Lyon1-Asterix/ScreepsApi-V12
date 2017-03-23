#include "Api-V12/Api.hpp"

#include "Api-V12/Routers/Client.hpp"

namespace V12 {

std::vector<std::string> split(const std::string& s, const std::string& delim)
{
        std::vector<std::string> result;
        size_t delimPos(0);
        size_t nextPos(0);
        while ((nextPos=s.find_first_of(delim, delimPos)) != std::string::npos)
        {
                result.push_back(s.substr(delimPos, nextPos-delimPos));
                delimPos = s.find_first_not_of(delim, nextPos);
        }
        if (delimPos != std::string::npos && delimPos < s.size())
                result.push_back(s.substr(delimPos));
        return result;
}

std::vector<std::string> split(const std::string& s)
{
        return split(s, "\t ");
}

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

bool Api::initialized ()
{
    return m_initialized;
}
/*
*/

void Api::socketAuthCB ( std::string m )
{
    std::cout << "Socket auth done" << std::endl;
    m_pSocket->unsubscribe ( "auth" );

    std::vector<std::string> args(split(m));
    if ( args[0] == "auth" ) {
        if ( args[1] == "ok" )
        {
            setToken ( args[2] );
            m_initialized = true;
            std::cout << "Socket auth ok" << std::endl;
        }
    }

}

bool Api::Signin ( std::string email, std::string password )
{
    m_initialized = false;
    nlohmann::json content, reply;
    content["email"] = email;
    content["password"] = password;
    reply = to_json ( m_client["api"]["auth"].route ( "signin", content.dump () ) );
    if ( reply.find ( "ok" ) == reply.end () ) return false;
    if ( reply["ok"].get<int>() != 1) return false;
    /**/
    if ( m_pSocket ) {
        std::cout << "send socket auth message" << std::endl;
        m_pSocket->subscribe ( "auth", std::bind ( &Api::socketAuthCB, this, std::placeholders::_1 ) );
        m_pSocket->send ( "auth " + reply["token"].get<std::string>() );
    }
    else
    {
        /**/
        setToken (reply["token"].get<std::string>());
        m_initialized = true;
    }
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
    if ( ! m_pSocket ) return;
}

void Api::RoomListener (std::string room, std::function<void(nlohmann::json)> callback)
{
    if ( ! m_pSocket ) return;
    m_pSocket->send ( "subscribe room:"+room );
}

void Api::WorldListener (std::function<void(nlohmann::json)> callback)
{
    if ( ! m_pSocket ) return;
}

void Api::UserListener (std::function<void(nlohmann::json)> callback)
{
    if ( ! m_pSocket ) return;
}

}
