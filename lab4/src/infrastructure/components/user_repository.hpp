#pragma once

#include <userver/components/loggable_component_base.hpp>
#include <application/user_service.hpp>

namespace lab4::infrastructure {

class UserRepositoryComponent final : public userver::components::LoggableComponentBase {
public:
    static constexpr std::string_view kName = "user-repository-component";

    UserRepositoryComponent(const userver::components::ComponentConfig& config,
                            const userver::components::ComponentContext& context);

    std::shared_ptr<lab4::application::IUserRepository> GetRepository() const;

private:
    std::shared_ptr<lab4::application::IUserRepository> userRepo_;
};

}