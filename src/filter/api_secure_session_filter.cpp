#include "api_secure_session_filter.hpp"
#include "drogon/HttpRequest.h"
#include "drogon/HttpResponse.h"
#include "drogon/HttpTypes.h"
#include <glog/logging.h>

namespace api 
{
    void api_secure_session_filter::doFilter(const HttpRequestPtr& req, FilterCallback&& fcb, FilterChainCallback &&fccb)
    {

        if (req->session()->getOptional<bool>("is_verified").has_value())
        {
            if (req->session()->getOptional<bool>("is_verified").value())
            {
                fccb();
                return;
            }
        }
        
        fcb(HttpResponse::newHttpResponse(HttpStatusCode::k401Unauthorized, ContentType::CT_NONE));
    }
}