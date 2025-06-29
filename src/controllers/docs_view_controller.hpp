#pragma once

#include <drogon/HttpSimpleController.h>

using namespace drogon;

class docs_view_controller final : public drogon::HttpSimpleController<docs_view_controller>
{
  public:
    void asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) override;
    PATH_LIST_BEGIN
    PATH_ADD("/", Get);
    PATH_LIST_END
};
