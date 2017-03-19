#include "Api-V12/Routers/Client.hpp"

#include "Api-V12/Routers/Api.hpp"
#include "Api-V12/Routers/Socket.hpp"

#include "Api-V12/Api.hpp"

namespace V12 {

Client::Client(Api* pApi) :
    ScreepsApi::Client ( pApi )
{
    new ModuleApi ( this );
    new Socket ( this );
}

}
