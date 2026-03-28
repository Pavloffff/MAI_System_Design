#include <application/user_component.hpp>
#include <userver/components/component_config.hpp>
#include <application/user_service.hpp>
#include <infrastructure/jwt/jwt.hpp>

namespace lab2::application {

UserServiceComponent::UserServiceComponent(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : LoggableComponentBase(config, context)
{
    const auto& jwtComponent = context.FindComponent<infrastructure::JwtAuthComponent>();
    auto tokenRepo = std::make_shared<infrastructure::JwtTokenRepository>(jwtComponent.GetGenerator());

    auto userRepo = std::make_shared<infrastructure::InMemoryUserRepository>();
    auto hasher = std::make_shared<infrastructure::SslPasswordHasher>();

    userService_ = std::make_shared<lab2::application::UserService>(
        userRepo, tokenRepo, hasher
    );
}

std::shared_ptr<lab2::application::UserService> UserServiceComponent::GetService() const {
    return userService_;
}

}  // namespace lab2::application