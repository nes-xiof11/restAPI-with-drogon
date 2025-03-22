#include "api_v1_auth.hpp"
#include "drogon/HttpRequest.h"
#include "drogon/HttpResponse.h"
#include "json/value.h"
#include <functional>
#include <tuple>
#include "../models/model.hpp"
#include "../service/user.hpp"
#include "drogon/HttpTypes.h"

namespace api 
{
namespace v1 
{

    auto api_v1_login::get_user_service()
    {
        static auto storage = model::get_storage();
        static auto service = service::user(storage);
        return service;
    }

    void api_v1_login::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr&)> &&callback)
    {
        auto response = HttpResponse::newHttpResponse();
        auto body = Json::Value();
        if (auto message = req->getJsonObject())
        {
            auto [email, password] = std::make_tuple(
                (*message)["email"].asString(),
                (*message)["password"].asString()
            );

            if (get_user_service().is_valide(email, password))
            {
                response->setStatusCode(HttpStatusCode::k202Accepted);
                req->session()->insert("is_verified", true);
                req->session()->insert("user_email", email);
                
            } else {
                response->setStatusCode(HttpStatusCode::k401Unauthorized);
            }

            callback(response);
            return;
        }
        response->setStatusCode(HttpStatusCode::k400BadRequest);
        callback(response);
    }
}
}