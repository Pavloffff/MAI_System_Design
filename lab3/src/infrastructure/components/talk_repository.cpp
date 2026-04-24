#include <infrastructure/components/talk_repository.hpp>
#include <infrastructure/postgres/talk_repository.hpp>
#include <userver/components/component_context.hpp>
#include <userver/storages/postgres/component.hpp>

namespace lab3::infrastructure {

TalkRepositoryComponent::TalkRepositoryComponent(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : LoggableComponentBase(config, context)
{
    auto cluster = context.FindComponent<userver::components::Postgres>("postgres-db").GetCluster();
    talkRepo_ = std::make_shared<lab3::infrastructure::PostgresTalkRepository>(cluster);
}

std::shared_ptr<lab3::application::ITalkRepository> TalkRepositoryComponent::GetRepository() const
{
    return talkRepo_;
}

}