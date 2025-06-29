//
// Created by eloide-novela on 29-06-2025.
//

#include "api_v1_logout.hpp"

namespace api
{
namespace v1
{
    void api_v1_logout::asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
        if (auto &session = req->getSession()) {
            session->erase("is_verified");
            return callback(HttpResponse::newHttpResponse(HttpStatusCode::k200OK, ContentType::CT_NONE));
        }
        return callback(HttpResponse::newHttpResponse(HttpStatusCode::k503ServiceUnavailable, ContentType::CT_NONE));
    }
}
}
