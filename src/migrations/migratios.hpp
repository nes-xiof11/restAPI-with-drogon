#pragma once

#include "api_token.hpp"
#include "user.hpp"
#include "json/value.h"
#include "../models/model.hpp"

namespace migration 
{
    inline void migrate(const Json::Value& config)
    {   
        static auto storage = model::get_storage();
        LOG(INFO) << __FUNCTION__;
        api_token::apply(storage, config["api-token"]);
        user::apply(storage, config["user"]);
    }
}