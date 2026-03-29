#include <application/talk_component.hpp>
#include <interfaces/rest/talks/talks_handler.hpp>
#include <docs/definitions/talks.hpp>
#include <userver/components/component_context.hpp>

namespace lab2::interfaces {

TalkCreateHandler::TalkCreateHandler(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : HttpHandlerBase(config, context),
    talkService_(context.FindComponent<lab2::application::TalkServiceComponent>().GetService())
{
}

std::string TalkCreateHandler::HandleRequestThrow(
    const userver::server::http::HttpRequest& request,
    userver::server::request::RequestContext& context) const
{
    try {
        request.GetHttpResponse().SetContentType(userver::http::content_type::kApplicationJson);

        auto requestJson = userver::formats::json::FromString(request.RequestBody());
        auto createTalkDto = requestJson.As<lab2::talks::CreateTalkRequestBody>();
        
        auto tokenUserId = std::stoi(context.GetData<std::string>("user_id"));
        createTalkDto.user_id = tokenUserId;

        auto response = talkService_->CreateTalk(createTalkDto);

        userver::formats::json::ValueBuilder responseJson(response);
        return userver::formats::json::ToString(responseJson.ExtractValue());
    } catch (const std::exception& e) {
        LOG_ERROR() << "Failed: " << e.what();

        throw userver::server::handlers::InternalServerError(
            userver::formats::json::MakeObject(
                "message", "Internal server error"
            )
        );
    }
}

TalkGetAllHandler::TalkGetAllHandler(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : HttpHandlerBase(config, context),
    talkService_(context.FindComponent<lab2::application::TalkServiceComponent>().GetService())
{
}

std::string TalkGetAllHandler::HandleRequestThrow(
    const userver::server::http::HttpRequest& request,
    userver::server::request::RequestContext& context) const
{
    try {
        auto talks = talkService_->GetTalks();
        
        userver::formats::json::ValueBuilder itemsBuilder;
        for (auto talk : talks) {
            userver::formats::json::ValueBuilder talkJson(talk);
            itemsBuilder.PushBack(talkJson.ExtractValue());
        }

        userver::formats::json::ValueBuilder responseJson(itemsBuilder);
        return userver::formats::json::ToString(responseJson.ExtractValue());
    } catch (const std::exception& e) {
        LOG_ERROR() << "Failed: " << e.what();

        throw userver::server::handlers::InternalServerError(
            userver::formats::json::MakeObject(
                "message", "Internal server error"
            )
        );
    }
}

}
