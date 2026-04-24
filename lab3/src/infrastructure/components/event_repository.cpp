#include <infrastructure/components/event_repository.hpp>
#include <infrastructure/postgres/event_repository.hpp>
#include <userver/components/component_context.hpp>
#include <userver/storages/postgres/component.hpp>

namespace lab3::infrastructure {

EventRepositoryComponent::EventRepositoryComponent(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : LoggableComponentBase(config, context)
{
    auto cluster = context.FindComponent<userver::components::Postgres>("postgres-db").GetCluster();
    eventRepo_ = std::make_shared<lab3::infrastructure::PostgresEventRepository>(cluster);
}

std::shared_ptr<lab3::application::IEventRepository> EventRepositoryComponent::GetRepository() const
{
    return eventRepo_;
}

}