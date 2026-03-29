#include <infrastructure/components/user_repository.hpp>

namespace lab2::infrastructure {

UserRepositoryComponent::UserRepositoryComponent(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : LoggableComponentBase(config, context)
{
    userRepo_ = std::make_shared<lab2::infrastructure::InMemoryUserRepository>();
}

std::shared_ptr<lab2::infrastructure::InMemoryUserRepository> UserRepositoryComponent::GetRepository() const
{
    return userRepo_;
}

}