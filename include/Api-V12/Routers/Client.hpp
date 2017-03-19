#ifndef Screeps_Client_Hpp
#define Screeps_Client_Hpp

#include "ScreepsApi/Client.hpp"

namespace V12 {

class Api;

class Client : public ScreepsApi::Client
{
public:
    Client(Api* pApi);
};

}

#endif
