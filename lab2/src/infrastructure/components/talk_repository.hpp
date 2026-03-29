#pragma once

#include <userver/components/loggable_component_base.hpp>
#include <infrastructure/in_memory/talk_repository.hpp>
namespace lab2::infrastructure {

class TalkRepositoryComponent final : public userver::components::LoggableComponentBase {
public:
    static constexpr std::string_view kName = "talk-repository-component";
    
    TalkRepositoryComponent(const userver::components::ComponentConfig& config,
                            const userver::components::ComponentContext& context);
    
    std::shared_ptr<lab2::infrastructure::InMemoryTalkRepository> GetRepository() const;

private:
    std::shared_ptr<lab2::infrastructure::InMemoryTalkRepository> talkRepo_;
};

}