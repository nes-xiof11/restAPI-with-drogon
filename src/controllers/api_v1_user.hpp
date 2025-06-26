#pragma once

#include "drogon/HttpController.h"
#include "drogon/HttpRequest.h"
#include "drogon/HttpResponse.h"
#include "drogon/HttpTypes.h"
#include <drogon/drogon.h>
#include <functional>
using namespace drogon;

namespace api 
{
namespace v1 
{
    class user: public HttpController<user>
    {
        auto get_service();
        public:
            METHOD_LIST_BEGIN
            ADD_METHOD_TO(user::create, "/api/v1/user/", Post, "api::api_token_filter", "api::api_session_filter");
            ADD_METHOD_TO(user::single, "/api/v1/user?user_id={1}", Get, "api::api_token_filter", "api::api_session_filter");
            ADD_METHOD_TO(user::list, "/api/v1/user/list/", Get, "api::api_token_filter", "api::api_session_filter");
            ADD_METHOD_TO(user::update, "/api/v1/user?user_id={1}", Put, "api::api_token_filter", "api::api_session_filter");
            ADD_METHOD_TO(user::remove, "/api/v1/user?user_id={1}", Delete, "api::api_token_filter", "api::api_session_filter");
            METHOD_LIST_END

            void create(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr&)>&&callback);
            void single(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr&)> &&callback, long user_id);
            void list(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr&)> &&callback);
            void update(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr&)> &&callback, long user_id);
            void remove(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr&)> &&callback, long user_id);
    };
}
}