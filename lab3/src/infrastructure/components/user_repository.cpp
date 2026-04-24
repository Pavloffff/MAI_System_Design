#include <infrastructure/components/user_repository.hpp>
#include <infrastructure/postgres/user_repository.hpp>
#include <userver/components/component_context.hpp>
#include <userver/storages/postgres/component.hpp>

namespace lab3::infrastructure {

UserRepositoryComponent::UserRepositoryComponent(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : LoggableComponentBase(config, context)
{
    auto cluster = context.FindComponent<userver::components::Postgres>("postgres-db").GetCluster();
    userRepo_ = std::make_shared<lab3::infrastructure::PostgresUserRepository>(cluster);
}

std::shared_ptr<lab3::application::IUserRepository> UserRepositoryComponent::GetRepository() const
{
    return userRepo_;
}

}