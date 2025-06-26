#pragma once

#include "drogon/HttpSimpleController.h"
#include <drogon/drogon.h>

using namespace drogon;

namespace api 
{
namespace v1 
{
    class sign_in final: public HttpSimpleController<sign_in>
    {
        auto get_service();
        public:
            void asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr&)> &&callback) override;
            PATH_LIST_BEGIN
                PATH_ADD("/api/v1/sign/in/", "api::api_token_filter", Post);
            PATH_LIST_END
    };
}
}