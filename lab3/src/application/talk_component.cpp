#include <application/talk_component.hpp>
#include <userver/components/component_config.hpp>
#include <infrastructure/components/talk_repository.hpp>
#include <infrastructure/components/user_repository.hpp>

namespace lab3::application {

TalkServiceComponent::TalkServiceComponent(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : LoggableComponentBase(config, context)
{
    auto talkRepo = context.FindComponent<lab3::infrastructure::TalkRepositoryComponent>().GetRepository();
    auto userRepo = context.FindComponent<lab3::infrastructure::UserRepositoryComponent>().GetRepository();
    talkService_ = std::make_shared<lab3::application::TalkService>(talkRepo, userRepo);   
}

std::shared_ptr<lab3::application::TalkService> TalkServiceComponent::GetService() const
{
    return talkService_;
}

} // namespace lab3::application