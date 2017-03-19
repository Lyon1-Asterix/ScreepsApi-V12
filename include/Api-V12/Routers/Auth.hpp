#ifndef Screeps_Auth_Hpp
#define Screeps_Auth_Hpp

#include "ScreepsApi/Module.hpp"

#include "Api-V12/Routers/Api.hpp"

namespace V12 {

class Auth : public ScreepsApi::Module
{
    public:
        Auth (ModuleApi* pApi);
    protected:
};

}

#endif
