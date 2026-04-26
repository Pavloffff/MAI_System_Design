#pragma once

#include <userver/components/loggable_component_base.hpp>
#include <userver/components/component_context.hpp>
#include <userver/components/component_config.hpp>

#include <application/event_service.hpp>

namespace lab4::application {

class EventServiceComponent final : public userver::components::LoggableComponentBase {
public:
    static constexpr std::string_view kName = "event-service-component";

    EventServiceComponent(const userver::components::ComponentConfig& config,
                          const userver::components::ComponentContext& context);
    
    std::shared_ptr<lab4::application::EventService> GetService() const;

private:
    std::shared_ptr<lab4::application::EventService> eventService_;
};

} // namespace lab4::application
