#include "api_v1_user.hpp"
#include "../models/model.hpp"
#include "../service/user.hpp"
#include "drogon/HttpRequest.h"
#include "drogon/HttpResponse.h"
#include "drogon/HttpTypes.h"
#include "json/value.h"
#include <functional>
#include <tuple>

namespace api 
{
namespace v1 
{
    auto user::get_service() 
    {
        static auto storage = model::get_storage();
        static auto service = service::user(storage);
        return service;
    }

    void user::create(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr&)> &&callback)
    {
        auto response = HttpResponse::newHttpResponse();
        auto body = Json::Value();
        if (auto message = req->getJsonObject())
        {
            const auto [name, nickname, email, password] = std::make_tuple(
                (*message)["name"].asString(),
                (*message)["nickname"].asString(),
                (*message)["email"].asString(),
                (*message)["password"].asString()
            );

            model::user created_user = {
                .name = name,
                .nickname = nickname,
                .email = email,
                .password = password
            };

            if ((created_user.id = get_service().create(created_user)) != -1) 
            {
                response->setStatusCode(HttpStatusCode::k201Created);
                body = model::user::to_json(created_user);
            } else {
                body["message"] = "Pode ser que o usuario ja exista";
                response->setStatusCode(HttpStatusCode::k500InternalServerError);
            }

            response->setBody(body.toStyledString());
            return callback(response);
        }

        response->setStatusCode(HttpStatusCode::k400BadRequest);
        callback(response);
    }

    void user::single(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr&)> &&callback, long user_id)
    {
        auto response = HttpResponse::newHttpResponse();
        auto body = Json::Value();
        auto user = get_service().get_by_id(user_id);

        if (user.has_value())
        {
            body = model::user::to_json(user.value().front());
        }
        response->setBody(body.toStyledString());
        response->setStatusCode(HttpStatusCode::k200OK);
        return callback(response);
    }

    void user::list(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr&)> &&callback)
    {
        auto response = HttpResponse::newHttpResponse();
        auto body = Json::Value();
        auto users = get_service().get_all();
        if (users.has_value())
        {
            for (const auto& user: users.value())
            {
                body.append(model::user::to_json(user));
            }
        }

        response->setBody(body.toStyledString());
        response->setStatusCode(HttpStatusCode::k200OK);
        return callback(response);
    }

    void user::update(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr&)> &&callback, long user_id)
    {
        auto response = HttpResponse::newHttpResponse();
        auto body = Json::Value();
        if (auto message = req->getJsonObject())
        {
            const auto [name, nickname, email, password] = std::make_tuple(
                (*message)["name"].asString(),
                (*message)["nickname"].asString(),
                (*message)["email"].asString(),
                (*message)["password"].asString()
            );

            auto updated_user = model::user{
                .id = user_id,
                .name = name,
                .nickname = nickname,
                .email = email,
                .password = password
            };

            if (get_service().update(updated_user))
            {
                body = model::user::to_json(updated_user);
                response->setStatusCode(HttpStatusCode::k202Accepted);
            } else {
                response->setStatusCode(HttpStatusCode::k500InternalServerError);
            }
            response->setBody(body.toStyledString());
            return callback(response);
        }
        response->setStatusCode(HttpStatusCode::k400BadRequest);
        callback(response);
    }

    void user::remove(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr&)> &&callback, long user_id)
    {
        return callback(
            (get_service().remove_by_id(user_id))
            ? HttpResponse::newHttpResponse(HttpStatusCode::k200OK, ContentType::CT_NONE)
            : HttpResponse::newHttpResponse(HttpStatusCode::k500InternalServerError, ContentType::CT_NONE)
        );
    }
}
}