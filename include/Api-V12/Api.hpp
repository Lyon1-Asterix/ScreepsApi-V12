#ifndef Screeps_Api_Hpp
#define Screeps_Api_Hpp

#include "ScreepsApi/Api.hpp"
#include "Api-V12/Routers/Client.hpp"

namespace V12 {

class Api : public ScreepsApi::Api
{
public:
    Api(std::shared_ptr<ScreepsApi::Web::Client> pClient);
    /*
    */
    virtual bool Signin ( std::string email, std::string password );
    virtual bool PullCode ( std::string branch );
    virtual bool PushCode ( std::string branch );
    virtual bool Console ( std::string command );
    virtual bool Room ( std::string name );
    //
    virtual bool AddSpawn ( std::string name, std::string x, std::string y );
protected:
    Client m_client;
    bool m_initialized;
};

}

#endif
