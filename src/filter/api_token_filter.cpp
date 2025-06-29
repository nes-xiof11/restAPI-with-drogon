#include "api_token_filter.hpp"
#include "drogon/HttpRequest.h"
#include "../models/model.hpp"
#include "../service/api_token.hpp"
#include "drogon/HttpResponse.h"
#include "drogon/HttpTypes.h"

extern std::unordered_map<std::string, bool> tokens;

namespace api
{
    auto api_token_filter::get_service()
    {
        static auto storage = model::get_storage();
        static auto service = service::api_token(storage);
        return service;
    }

    void api_token_filter::doFilter(const HttpRequestPtr& req, FilterCallback&& fcb, FilterChainCallback &&fccb)
    {
        auto token = req->getHeader("api-token");
        bool is_authorized = false;
        if (not tokens.empty() && tokens[token])
            is_authorized = true;
        else if (get_service().validate(token))
            is_authorized = true;

        if (is_authorized)
        {
            //Passed
            fccb();
            return;
        }
        //Check failed
        fcb(HttpResponse::newHttpResponse(HttpStatusCode::k401Unauthorized, ContentType::CT_NONE));
    }
}