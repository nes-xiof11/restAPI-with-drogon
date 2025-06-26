#pragma once

#include "drogon/HttpRequest.h"
#include <drogon/drogon.h>
using namespace drogon;

namespace api 
{
    class api_session_filter final: public HttpFilter<api_session_filter>
    {
        public:
            void doFilter(const HttpRequestPtr& req, FilterCallback&& fcb,FilterChainCallback&& fccb) override;
    };
}