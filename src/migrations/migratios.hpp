#pragma once

#include "api_token.hpp"
#include "user.hpp"
#include "json/value.h"
namespace migration 
{
    inline void migrate(const Json::Value& config)
    {   
        LOG(INFO) << __FUNCTION__;
        api_token::apply(config["api-token"]);
        user::apply(config["user"]);
    }
}