#include <application/event_component.hpp>
#include <interfaces/rest/events/events_handler.hpp>
#include <docs/definitions/events.hpp>
#include <userver/components/component_context.hpp>

namespace lab3::interfaces {

EventCreateHandler::EventCreateHandler(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : HttpHandlerBase(config, context),
    eventService_(context.FindComponent<lab3::application::EventServiceComponent>().GetService())
{
}

std::string EventCreateHandler::HandleRequestThrow(
    const userver::server::http::HttpRequest& request,
    userver::server::request::RequestContext& context) const
{
    try {
        request.GetHttpResponse().SetContentType(userver::http::content_type::kApplicationJson);

        auto requestJson = userver::formats::json::FromString(request.RequestBody());
        auto createEventDto = requestJson.As<lab3::events::CreateEventRequestBody>();

        auto tokenUserId = std::stoi(context.GetData<std::string>("user_id"));
        createEventDto.user_id = tokenUserId;

        auto response = eventService_->CreateEvent(createEventDto);

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

EventAddTalkHandler::EventAddTalkHandler(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : HttpHandlerBase(config, context),
    eventService_(context.FindComponent<lab3::application::EventServiceComponent>().GetService())
{
}

std::string EventAddTalkHandler::HandleRequestThrow(
    const userver::server::http::HttpRequest& request,
    userver::server::request::RequestContext& context) const
{
    try {
        request.GetHttpResponse().SetContentType(userver::http::content_type::kApplicationJson);

        lab3::domain::EventId eventId = lab3::domain::EventId(std::stoll(request.GetPathArg("event_id")));
        lab3::domain::TalkId talkId = lab3::domain::TalkId(std::stoll(request.GetPathArg("talk_id")));
        lab3::domain::UserId tokenUserId = lab3::domain::UserId(std::stoll(context.GetData<std::string>("user_id")));

        auto response = eventService_->AddTalkToEvent(eventId, talkId, tokenUserId);
        
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

EventGetTalksHandler::EventGetTalksHandler(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : HttpHandlerBase(config, context),
    eventService_(context.FindComponent<lab3::application::EventServiceComponent>().GetService())
{
}

std::string EventGetTalksHandler::HandleRequestThrow(
    const userver::server::http::HttpRequest& request,
    userver::server::request::RequestContext& context) const
{
    try {
        request.GetHttpResponse().SetContentType(userver::http::content_type::kApplicationJson);

        lab3::domain::EventId eventId = lab3::domain::EventId(std::stoll(request.GetPathArg("event_id")));

        auto events = eventService_->GetEventTalks(eventId);

        userver::formats::json::ValueBuilder itemsBuilder;
        for (auto event : events) {
            userver::formats::json::ValueBuilder eventJson(event);
            itemsBuilder.PushBack(eventJson.ExtractValue());
        }

        return userver::formats::json::ToString(itemsBuilder.ExtractValue());
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