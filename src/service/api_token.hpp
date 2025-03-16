#pragma once

#include "crud.hpp"
#include "../models/api_token.hpp"
#include "sqlite_orm/sqlite_orm.h"
namespace service 
{
    template <typename Storage>
    class api_token: public crud<Storage, model::api_token>
    {
        public:
            explicit api_token(Storage& storage): crud<Storage, model::api_token>(storage)
            { }

            bool validate(const std::string& token)
            {
                using namespace sqlite_orm;
                if (this->storage.template count<model::api_token>(where(c(&model::api_token::token) == token)))
                {
                    return true;
                }
                return false;
            }
    };
}