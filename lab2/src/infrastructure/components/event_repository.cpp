#include <infrastructure/components/event_repository.hpp>

namespace lab2::infrastructure {

EventRepositoryComponent::EventRepositoryComponent(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : LoggableComponentBase(config, context)
{
    eventRepo_ = std::make_shared<lab2::infrastructure::InMemoryEventRepository>();
}

std::shared_ptr<lab2::infrastructure::InMemoryEventRepository> EventRepositoryComponent::GetRepository() const
{
    return eventRepo_;
}

}