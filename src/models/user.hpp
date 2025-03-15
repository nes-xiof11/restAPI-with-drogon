#pragma once

#include "json/value.h"
#include <string>
#include <json/json.h>
#include <sqlite_orm/sqlite_orm.h>

namespace model 
{
    struct user 
    {   
        long id;
        std::string name,
                    nickname,
                    email,
                    password;
        std::string created_at,
                    updated_at;

        static Json::Value to_json(const model::user& sub)
        {
            Json::Value json;
            json["id"] = sub.id;
            json["name"] = sub.name;
            json["nickname"] = sub.nickname;
            json["email"] = sub.email;
            json["password"] = sub.password;
            json["created_at"] = sub.created_at;
            json["updated_at"] = sub.updated_at;
            return json;
        }

        static model::user from_json(const Json::Value& json)
        {
            model::user sub;
            sub.id = json["id"].asUInt64();
            sub.name = json["name"].asString();
            sub.nickname = json["nickname"].asString();
            sub.email = json["email"].asString();
            sub.password = json["password"].asString();
            sub.created_at = json["created_at"].asString();
            sub.updated_at = json["updated_at"].asString();
            return sub;
        }

        static auto make_table()
        {
            using namespace sqlite_orm;
            return sqlite_orm::make_table(
                "users",
                make_column("id", &model::user::id, primary_key().autoincrement()),
                make_column("name", &model::user::name),
                make_column("nickname", &model::user::nickname),
                make_column("email", &model::user::email, unique()),
                make_column("password", &model::user::password),
                make_column("created_at", &model::user::created_at),
                make_column("updated_at", &model::user::updated_at)
            );
        }        
    };
}