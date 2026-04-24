#pragma once

#include <userver/components/loggable_component_base.hpp>
#include <application/talk_service.hpp>

namespace lab3::infrastructure {

class TalkRepositoryComponent final : public userver::components::LoggableComponentBase {
public:
    static constexpr std::string_view kName = "talk-repository-component";
    
    TalkRepositoryComponent(const userver::components::ComponentConfig& config,
                            const userver::components::ComponentContext& context);
    
    std::shared_ptr<lab3::application::ITalkRepository> GetRepository() const;

private:
    std::shared_ptr<lab3::application::ITalkRepository> talkRepo_;
};

}