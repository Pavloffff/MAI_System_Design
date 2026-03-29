#pragma once

#include <userver/components/loggable_component_base.hpp>
#include <userver/components/component_context.hpp>
#include <userver/components/component_config.hpp>

#include <application/talk_service.hpp>

namespace lab2::application {

class TalkServiceComponent final : public userver::components::LoggableComponentBase {
public:
    static constexpr std::string_view kName = "talk-service-component";

    TalkServiceComponent(const userver::components::ComponentConfig& config,
                         const userver::components::ComponentContext& context);

    std::shared_ptr<lab2::application::TalkService> GetService() const;

private:
    std::shared_ptr<lab2::application::TalkService> talkService_;
};

} // namespace lab2::application