#include <application/user_component.hpp>
#include <userver/components/component_config.hpp>
#include <application/user_service.hpp>
#include <infrastructure/components/jwt.hpp>
#include <infrastructure/jwt/jwt_token_repository.hpp>
#include <infrastructure/components/hasher.hpp>
#include <infrastructure/components/user_repository.hpp>

namespace lab4::application {

UserServiceComponent::UserServiceComponent(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : LoggableComponentBase(config, context)
{
    const auto& jwtComponent = context.FindComponent<infrastructure::JwtAuthComponent>();
    auto tokenRepo = std::make_shared<infrastructure::JwtTokenRepository>(jwtComponent.GetGenerator());

    auto userRepo = context.FindComponent<infrastructure::UserRepositoryComponent>().GetRepository();
    auto hasher = context.FindComponent<infrastructure::HasherComponent>().GetHasher();

    userService_ = std::make_shared<lab4::application::UserService>(
        userRepo, tokenRepo, hasher
    );
}

std::shared_ptr<lab4::application::UserService> UserServiceComponent::GetService() const {
    return userService_;
}

}  // namespace lab4::application