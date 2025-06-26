#pragma once
#include "drogon/HttpFilter.h"
#include "drogon/HttpRequest.h"
#include <drogon/drogon.h>

using namespace drogon;

namespace api 
{
    class api_token_filter final: public HttpFilter<api_token_filter>
    {
        auto get_service();
        public:
            void doFilter(const HttpRequestPtr& req, FilterCallback&& fcb, FilterChainCallback&& fccb) override;
    };
}