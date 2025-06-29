#pragma once

#include "json/value.h"
#include "../service/api_token.hpp"

std::unordered_map<std::string, bool> tokens;

namespace migration 
{
namespace api_token 
{
    template <typename Storage>
    inline void apply(Storage& storage, const Json::Value &m)
    {
        auto service = service::api_token(storage);
        for (const auto &api_token: m)
        {
            auto created_api_token = model::api_token::to_json(api_token);
            if (service.create(created_api_token) == (-1))
                LOG(WARNING) << "api-token was not created";
        }

        auto all = service.get_all(0);
        for (const auto &api_token: *all)
            tokens[api_token.token] = true;
    }
}
}