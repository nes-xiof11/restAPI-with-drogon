#pragma once
#include "../models/model.hpp"
#include "../service/user.hpp"
#include "json/value.h"

namespace migration 
{
namespace user 
{   
    inline void apply(const Json::Value& m)
    {
        static auto storage = model::get_storage();
        static auto service = service::user(storage);
        for (auto &user: m) 
        {   
            auto created_user = model::user::from_json(user);
            std::cout << created_user.name << std::endl;
            if (service.create(created_user) == (-1))
                LOG(WARNING) << "user as named: " << created_user.name << " was not created";
        }
    }
}
}