#include "api_v1_signin.hpp"
#include "../models/model.hpp"
#include "../service/user.hpp"
#include "drogon/HttpRequest.h"
#include "drogon/HttpResponse.h"
#include <functional>

namespace api 
{
namespace v1 
{
    auto sign_in::get_service()
    {
        static auto storage = model::get_storage();
        static auto service = service::user(storage);
        return service;
    }

    void sign_in::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr&)> &&callback)
    {

    }
}
}