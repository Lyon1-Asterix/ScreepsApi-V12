#ifndef Screeps_Game_Hpp
#define Screeps_Game_Hpp

#include "ScreepsApi/Module.hpp"

#include "Api-V12/Routers/Api.hpp"

namespace V12 {

class Game : public ScreepsApi::Module
{
public:
    Game (ModuleApi* pApi);
};

}

#endif
