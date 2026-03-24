#pragma once

#include <userver/server/handlers/http_handler_base.hpp>

namespace lab2::interfaces {

class UserLoginHandler final : public userver::server::handlers::HttpHandlerBase {
public:
    static constexpr std::string_view kName = "handler-user-login";

    using HttpHandlerBase::HttpHandlerBase;

    std::string HandleRequestThrow(
        const userver::server::http::HttpRequest& request,
        userver::server::request::RequestContext& context) const override;
};

}  // namespace lab2::interfaces