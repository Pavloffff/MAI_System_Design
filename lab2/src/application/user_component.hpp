#pragma once

#include <memory>
#include <string>

#include <userver/components/loggable_component_base.hpp>
#include <userver/components/component_context.hpp>
#include <userver/components/component_config.hpp>

#include <application/user_service.hpp>
#include <infrastructure/in_memory/user_repository.hpp>
#include <infrastructure/jwt/jwt_token_repository.hpp>
#include <infrastructure/ssl/password_hasher.hpp>

namespace lab2::application {

class UserServiceComponent final : public userver::components::LoggableComponentBase {
public:
    static constexpr std::string_view kName = "user-service-component";

    UserServiceComponent(const userver::components::ComponentConfig& config,
                         const userver::components::ComponentContext& context);

    std::shared_ptr<lab2::application::UserService> GetService() const;

private:
    std::shared_ptr<lab2::application::UserService> userService_;
};

} // namespace lab2::application