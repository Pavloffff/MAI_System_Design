#include <application/talk_component.hpp>
#include <infrastructure/in_memory/talk_repository.hpp>

namespace lab2::application {

TalkServiceComponent::TalkServiceComponent(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : LoggableComponentBase(config, context)
{
    auto talkRepo = lab2::infrastructure::InMemoryTalkRepository();
    talkService_ = std::make_shared<lab2::application::TalkService>(talkRepo);   
}

std::shared_ptr<lab2::application::TalkService> TalkServiceComponent::GetService() const
{
    return talkService_;
}

} // namespace lab2::application