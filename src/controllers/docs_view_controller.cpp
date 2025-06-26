#include "docs_view_controller.hpp"
#include "drogon/HttpRequest.h"
#include "drogon/HttpResponse.h"
#include <functional>

void docs_view_controller::asyncHandleHttpRequest(const HttpRequestPtr & req, std::function<void (const HttpResponsePtr&)> && callback)
{
    
}