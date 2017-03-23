#ifndef Screeps_Api_Hpp
#define Screeps_Api_Hpp

#include "ScreepsApi/Api.hpp"
#include "Api-V12/Routers/Client.hpp"

#include "nlohmann/json.hpp"

namespace V12 {

class Api : public ScreepsApi::Api
{
public:
    Api(std::shared_ptr<ScreepsApi::Web::Client> pClient,std::shared_ptr<ScreepsApi::Web::Socket> pSocket);
    /*
    */
    virtual bool Signin ( std::string email, std::string password );
    virtual bool PushCode ( std::string branch, std::map < std::string, std::string > modules );
    virtual bool Console ( std::string command );
    virtual bool AddSpawn ( std::string name, std::string x, std::string y );
    //
    virtual nlohmann::json User ();
    virtual nlohmann::json Room ( std::string name );
    virtual nlohmann::json PullCode ( std::string branch );
    //
    virtual void ConsoleListener (std::function<void(nlohmann::json)> callback);
    virtual void RoomListener (std::string room, std::function<void(nlohmann::json)> callback);
    virtual void WorldListener (std::function<void(nlohmann::json)> callback);
    virtual void UserListener (std::function<void(nlohmann::json)> callback);
protected:
    Client m_client;
    bool m_initialized;
    void socketAuthCB ( std::string m );
};

}

#endif
