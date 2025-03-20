#pragma once

#include "crud.hpp"
#include "../models/user.hpp"
#include <exception>
#include "../util/hash.hpp"

namespace service 
{   
    template <typename Storage>
    class user: public crud<Storage, model::user>
    {
        public:
            explicit user(Storage &storage): crud<Storage, model::user>(storage)
            { }

            long create(model::user& user) override {
                try {
                    user.created_at = this->get_current_datatime();
                    user.password = util::hash::encode(user.password);
                    return this->storage.template insert<model::user>(user);
                } catch (const std::exception& e) {
                    LOG(ERROR) << e.what();
                }
                return (-1);
            }
    };
}