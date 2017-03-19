#ifndef Screeps_Socket_Hpp
#define Screeps_Socket_Hpp

#include "ScreepsApi/Module.hpp"

#include "Api-V12/Routers/Client.hpp"

namespace V12 {

class Socket : public ScreepsApi::Module
{
    public:
        Socket (Client* pClient);
};

}

#endif
