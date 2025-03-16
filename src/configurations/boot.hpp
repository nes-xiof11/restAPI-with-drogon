#pragma once

#include "json/value.h"
namespace configuration 
{
    void setup_server(const Json::Value& config);
    void setup_directories(const Json::Value& config);
    void boot();
}