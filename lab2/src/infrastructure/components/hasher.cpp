#include <infrastructure/components/hasher.hpp>

namespace lab2::infrastructure {

HasherComponent::HasherComponent(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : LoggableComponentBase(config, context)
{
    hasher_ = std::make_shared<lab2::infrastructure::SslPasswordHasher>();
}

std::shared_ptr<lab2::infrastructure::SslPasswordHasher> HasherComponent::GetHasher() const
{
    return hasher_;
}

}