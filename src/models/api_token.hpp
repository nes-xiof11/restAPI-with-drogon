#pragma once

#include "sqlite_orm/sqlite_orm.h"
#include "json/value.h"
#include <string>

namespace model 
{
    struct api_token
    {
        int id;
        std::string token;
        std::string created_at,
                    updated_at;

        static Json::Value from_json(const model::api_token& sub)
        {
            Json::Value json;
            json["id"] = sub.id;
            json["token"] = sub.token;
            json["created_at"] = sub.created_at;
            json["updated_at"] = sub.updated_at;
            return json;
        }

        static model::api_token to_json(const Json::Value& json)
        {
            model::api_token sub;
            sub.id = json["id"].asInt();
            sub.token = json["token"].asString();
            sub.created_at = json["created_at"].asString();
            sub.updated_at = json["updated_at"].asString();
            return sub;
        }

        static auto make_table()
        {
            using namespace sqlite_orm;
            return sqlite_orm::make_table(
                "api_token",
                make_column("id", &model::api_token::id, primary_key().autoincrement()),
                make_column("token", &model::api_token::token, unique()),
                make_column("created_at", &model::api_token::created_at),
                make_column("updated_at", &model::api_token::updated_at)
            );
        }
    };

}