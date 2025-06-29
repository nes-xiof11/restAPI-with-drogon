#include "api_v1_user.hpp"
#include "../models/model.hpp"
#include "../service/user.hpp"
#include "drogon/HttpRequest.h"
#include "drogon/HttpResponse.h"
#include "drogon/HttpTypes.h"
#include "json/value.h"
#include <cstdlib>
#include <functional>

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
        
        if (auto & body = req->getJsonObject())
        {
            model::user created_user = model::user::from_json(*body);
            if ((created_user.id = get_service().create(created_user)) != -1) 
            {
                response->setStatusCode(HttpStatusCode::k200OK);
                response->newHttpJsonResponse(model::user::to_json(created_user));
            } else {
                response->setStatusCode(HttpStatusCode::k400BadRequest);
            }
            return callback(response);
        }

        response->setStatusCode(HttpStatusCode::k406NotAcceptable);
        callback(response);
    }

    void user::single(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr&)> &&callback, long user_id)
    {
        if (const auto & user = get_service().get_by_id(user_id))
        {
            callback(HttpResponse::newHttpJsonResponse(model::user::to_json(user.value())));
            return;
        } else
            callback(HttpResponse::newHttpResponse(HttpStatusCode::k404NotFound, ContentType::CT_NONE));
    }

    void user::list(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr&)> &&callback)
    {
        const int & offset = std::atoi(req->getParameter("offset").c_str());
        int limit = std::atoi(req->getParameter("limit").c_str());
        limit = (limit <= 0) ? 10 : limit;
        
        Json::Value items;
        items["items"] = Json::Value(Json::arrayValue);
        if (const auto & users = get_service().get_all(0, limit))
        {
            for (const auto & user : *users)
            {
                items["items"].append(model::user::to_json(user));
            }
            return callback(HttpResponse::newHttpJsonResponse(items));
        } else      
            return callback(HttpResponse::newHttpResponse(HttpStatusCode::k404NotFound, ContentType::CT_NONE));
    }

    void user::update(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr&)> &&callback, long user_id)
    {
        if (auto & body = req->getJsonObject())
        {
            auto updated_user = model::user::from_json(*body);

            if (get_service().update(updated_user))
            {
                return callback(HttpResponse::newHttpJsonResponse(model::user::to_json(updated_user)));
            } 
            else 
            {
                return callback(HttpResponse::newHttpResponse(HttpStatusCode::k400BadRequest, ContentType::CT_NONE));
            }
        }
        return callback(HttpResponse::newHttpResponse(HttpStatusCode::k406NotAcceptable, ContentType::CT_NONE));
    }

    void user::remove(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr&)> &&callback, long user_id)
    {
        return callback(
            (get_service().remove_by_id(user_id))
            ? HttpResponse::newHttpResponse(HttpStatusCode::k200OK, ContentType::CT_NONE)
            : HttpResponse::newHttpResponse(HttpStatusCode::k404NotFound, ContentType::CT_NONE)
        );
    }
}
}
