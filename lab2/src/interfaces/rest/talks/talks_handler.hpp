#pragma once

#include <userver/server/handlers/http_handler_base.hpp>
#include <application/talk_service.hpp>

namespace lab2::interfaces {

class TalkCreateHandler final : public userver::server::handlers::HttpHandlerBase {
public:
    static constexpr std::string_view kName = "handler-talk-create";

    TalkCreateHandler(
        const userver::components::ComponentConfig& config,
        const userver::components::ComponentContext& context);

    std::string HandleRequestThrow(
        const userver::server::http::HttpRequest& request,
        userver::server::request::RequestContext& context) const override;

private:
    std::shared_ptr<lab2::application::TalkService> talkService_;
};

class TalkGetAllHandler final : public userver::server::handlers::HttpHandlerBase {
public:
    static constexpr std::string_view kName = "handler-talk-get-all";

    TalkGetAllHandler(
        const userver::components::ComponentConfig& config,
        const userver::components::ComponentContext& context);

    std::string HandleRequestThrow(
        const userver::server::http::HttpRequest& request,
        userver::server::request::RequestContext& context) const override;

private:
    std::shared_ptr<lab2::application::TalkService> talkService_;
};

}