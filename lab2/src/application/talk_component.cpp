#include <application/talk_component.hpp>
#include <userver/components/component_config.hpp>
#include <infrastructure/components/talk_repository.hpp>
#include <infrastructure/components/user_repository.hpp>

namespace lab2::application {

TalkServiceComponent::TalkServiceComponent(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : LoggableComponentBase(config, context)
{
    auto talkRepo = context.FindComponent<lab2::infrastructure::TalkRepositoryComponent>().GetRepository();
    auto userRepo = context.FindComponent<lab2::infrastructure::UserRepositoryComponent>().GetRepository();
    talkService_ = std::make_shared<lab2::application::TalkService>(talkRepo, userRepo);   
}

std::shared_ptr<lab2::application::TalkService> TalkServiceComponent::GetService() const
{
    return talkService_;
}

} // namespace lab2::application