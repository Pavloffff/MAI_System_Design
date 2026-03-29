#include <infrastructure/components/talk_repository.hpp>

namespace lab2::infrastructure {

TalkRepositoryComponent::TalkRepositoryComponent(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : LoggableComponentBase(config, context)
{
    talkRepo_ = std::make_shared<lab2::infrastructure::InMemoryTalkRepository>();
}

std::shared_ptr<lab2::infrastructure::InMemoryTalkRepository> TalkRepositoryComponent::GetRepository() const
{
    return talkRepo_;
}

}