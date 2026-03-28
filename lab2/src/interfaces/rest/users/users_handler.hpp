#pragma once

#include <userver/server/handlers/http_handler_base.hpp>
#include <application/user_service.hpp>

namespace lab2::interfaces {

class UserLoginHandler final : public userver::server::handlers::HttpHandlerBase {
public:
    static constexpr std::string_view kName = "handler-user-login";

    UserLoginHandler(
        const userver::components::ComponentConfig& config,
        const userver::components::ComponentContext& context);

    std::string HandleRequestThrow(
        const userver::server::http::HttpRequest& request,
        userver::server::request::RequestContext& context) const override;

private:
    std::shared_ptr<lab2::application::UserService> userService_;
};

class UserUserCreateHandler final : public userver::server::handlers::HttpHandlerBase {
public:
    static constexpr std::string_view kName = "handler-user-create";

    UserUserCreateHandler(
        const userver::components::ComponentConfig& config,
        const userver::components::ComponentContext& context);
    
    std::string HandleRequestThrow(
        const userver::server::http::HttpRequest& request,
        userver::server::request::RequestContext& context) const override;

private:
    std::shared_ptr<lab2::application::UserService> userService_;
};

}  // namespace lab2::interfaces