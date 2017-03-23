
#include <iostream>

#include "ScreepsApi/Web.hpp"
#include "ScreepsApi/ApiManager.hpp"
#include "ScreepsApi/Api.hpp"

#include "Api-V12/Api.hpp"

namespace V12 {

std::shared_ptr < ScreepsApi::Api > createApiV12 ( std::shared_ptr < ScreepsApi::Web::Client > web,std::shared_ptr<ScreepsApi::Web::Socket> soc )
{
    std::shared_ptr < ScreepsApi::Api > out ( new V12::Api ( web,soc ) );
    return out;
}

static void __init() __attribute__((constructor));

void __init() {
    std::clog << "Registering V12 of C++ ScreepsApi\n";
    ScreepsApi::ApiManager::Instance ().registerCreator ( 12, createApiV12 );
}
static void __deinit() __attribute__((destructor));

void __deinit() {
}

}
