#pragma once

#include "json/value.h"
#include "../models/model.hpp"
#include "../service/api_token.hpp"

namespace migration 
{
namespace api_token 
{
    inline void apply(const Json::Value &m)
    {
        static auto storage = model::get_storage();
        static auto service = service::api_token(storage);
        for (const auto &api_token: m)
        {
            auto created_api_token = model::api_token::to_json(api_token);
            if (service.create(created_api_token) == (-1))
                LOG(WARNING) << "api-token was not created";
        }
    }
}
}