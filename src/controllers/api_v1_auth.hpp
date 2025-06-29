#pragma once

#include "drogon/HttpResponse.h"
#include "drogon/HttpSimpleController.h"
#include "drogon/HttpTypes.h"
#include <drogon/drogon.h>
#include <functional>

using namespace drogon;

namespace api 
{
namespace v1 
{
    class api_v1_login final : public HttpSimpleController<api_v1_login>
    {
        auto get_user_service();
        public:
            PATH_LIST_BEGIN
            PATH_ADD("/api/v1/login/", "api::api_token_filter", Post, Get);
            PATH_LIST_END
            
            void asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr&)> &&callback) override;
    };
}
}