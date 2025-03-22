#pragma once

#include "drogon/HttpRequest.h"
#include <drogon/drogon.h>
using namespace drogon;

namespace api 
{
    class api_secure_session_filter: public HttpFilter<api_secure_session_filter>
    {
        public:
            void doFilter(const HttpRequestPtr& req, FilterCallback&& fcb,FilterChainCallback&& fccb);
    };
}