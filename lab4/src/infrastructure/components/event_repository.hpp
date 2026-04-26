#pragma once

#include <userver/components/loggable_component_base.hpp>
#include <application/event_service.hpp>

namespace lab4::infrastructure {

class EventRepositoryComponent final : public userver::components::LoggableComponentBase {
public:
    static constexpr std::string_view kName = "event-repository-component";
    
    EventRepositoryComponent(const userver::components::ComponentConfig& config,
                            const userver::components::ComponentContext& context);
    
    std::shared_ptr<lab4::application::IEventRepository> GetRepository() const;

private:
    std::shared_ptr<lab4::application::IEventRepository> eventRepo_;
};

}