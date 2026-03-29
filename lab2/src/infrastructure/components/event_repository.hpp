#pragma once

#include <userver/components/loggable_component_base.hpp>
#include <infrastructure/in_memory/event_repository.hpp>

namespace lab2::infrastructure {

class EventRepositoryComponent final : public userver::components::LoggableComponentBase {
public:
    static constexpr std::string_view kName = "event-repository-component";
    
    EventRepositoryComponent(const userver::components::ComponentConfig& config,
                            const userver::components::ComponentContext& context);
    
    std::shared_ptr<lab2::infrastructure::InMemoryEventRepository> GetRepository() const;

private:
    std::shared_ptr<lab2::infrastructure::InMemoryEventRepository> eventRepo_;
};

}