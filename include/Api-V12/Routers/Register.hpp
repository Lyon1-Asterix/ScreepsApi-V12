#ifndef Screeps_Register_Hpp
#define Screeps_Register_Hpp

#include "ScreepsApi/Module.hpp"

#include "Api-V12/Routers/Api.hpp"

namespace V12 {

class Register : public ScreepsApi::Module
{
    public:
        Register (ModuleApi* pApi) ;
};

}

#endif
