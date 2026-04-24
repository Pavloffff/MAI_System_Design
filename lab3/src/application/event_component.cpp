#include <application/event_component.hpp>
#include <userver/components/component_config.hpp>
#include <infrastructure/components/event_repository.hpp>
#include <infrastructure/components/talk_repository.hpp>
#include <infrastructure/components/user_repository.hpp>

namespace lab3::application {

EventServiceComponent::EventServiceComponent(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : LoggableComponentBase(config, context)
{
    auto eventRepo = context.FindComponent<lab3::infrastructure::EventRepositoryComponent>().GetRepository();
    auto talkRepo = context.FindComponent<lab3::infrastructure::TalkRepositoryComponent>().GetRepository();
    auto userRepo = context.FindComponent<lab3::infrastructure::UserRepositoryComponent>().GetRepository();
    eventService_ = std::make_shared<lab3::application::EventService>(eventRepo, talkRepo, userRepo);   
}

std::shared_ptr<lab3::application::EventService> EventServiceComponent::GetService() const
{
    return eventService_;
}

} // namespace lab3::application