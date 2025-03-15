#pragma once

#include "crud.hpp"
#include "../models/user.hpp"

namespace service 
{   
    template <typename Storage>
    class user: public crud<Storage, model::user>
    {
        public:
            explicit user(Storage &storage): crud<Storage, model::user>(storage)
            { }
    };
}