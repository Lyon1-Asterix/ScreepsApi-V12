#ifndef Screeps_User_Hpp
#define Screeps_User_Hpp

#include "ScreepsApi/Module.hpp"

#include "Api-V12/Routers/Api.hpp"

namespace V12 {

class User : public ScreepsApi::Module
{
    public:
        User (ModuleApi* pApi);
};

}

#endif
