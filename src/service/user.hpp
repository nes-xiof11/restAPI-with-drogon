#pragma once

#include "crud.hpp"
#include "../models/user.hpp"
#include <exception>
#include "../util/hash.hpp"
#include "sqlite_orm/sqlite_orm.h"

namespace service 
{   
    template <typename Storage>
    class user final: public crud<Storage, model::user>
    {
        public:
            explicit user(Storage &storage): crud<Storage, model::user>(storage)
            { }

            long create(model::user& user) override 
            {
                try 
                {
                    user.password = util::hash::encode(user.password);
                    return crud<Storage, model::user>::create(user);
                } 
                catch (const std::exception& e) 
                {
                    LOG(ERROR) << e.what();
                }
                return (-1);
            }

            bool is_valide(const std::string& email, const std::string& password) 
            {
                try {
                    using namespace sqlite_orm;
                    if (this->storage.template count<model::user>(
                        where(and_((c(&model::user::email) == email), (c(&model::user::password) == util::hash::encode(password)))))
                    )
                    {
                        return true;
                    }
                    return false;
                } catch (const std::exception& e) {
                    LOG(ERROR) << e.what();
                }
                return false;
            }
    };
}