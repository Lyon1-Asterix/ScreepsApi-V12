#ifndef Screeps_ModuleApi_Hpp
#define Screeps_ModuleApi_Hpp

#include "ScreepsApi/Module.hpp"

#include "Api-V12/Routers/Client.hpp"

namespace V12 {

class ModuleApi : public ScreepsApi::Module
{
    public:
        ModuleApi (Client* pClient);
};

}

#endif
