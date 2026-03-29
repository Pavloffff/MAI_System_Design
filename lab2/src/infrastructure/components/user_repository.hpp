#pragma once

#include <userver/components/loggable_component_base.hpp>
#include <infrastructure/in_memory/user_repository.hpp>

namespace lab2::infrastructure {

class UserRepositoryComponent final : public userver::components::LoggableComponentBase {
public:
    static constexpr std::string_view kName = "user-repository-component";

    UserRepositoryComponent(const userver::components::ComponentConfig& config,
                            const userver::components::ComponentContext& context);

    std::shared_ptr<lab2::infrastructure::InMemoryUserRepository> GetRepository() const;

private:
    std::shared_ptr<lab2::infrastructure::InMemoryUserRepository> userRepo_;
};

}