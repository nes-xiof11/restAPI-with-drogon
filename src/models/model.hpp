#pragma once

#include <sqlite_orm/sqlite_orm.h>
#include "api_token.hpp"
#include "user.hpp"
#include "../configurations/configuration.hpp"
#include <iostream>

namespace model 
{
    inline auto get_storage()
    {
        static auto storage = sqlite_orm::make_storage(
            configuration::get_db_filename(),
            model::api_token::make_table(),
            model::user::make_table()
        );
        storage.sync_schema();
        for (const auto & [name, result]: storage.sync_schema())
        {
            std::cout << "[sync " << name << ": " << result << "]" << std::endl;
        }
        return storage;
    }
}