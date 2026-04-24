#include <infrastructure/components/hasher.hpp>

namespace lab3::infrastructure {

HasherComponent::HasherComponent(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : LoggableComponentBase(config, context)
{
    hasher_ = std::make_shared<lab3::infrastructure::SslPasswordHasher>();
}

std::shared_ptr<lab3::infrastructure::SslPasswordHasher> HasherComponent::GetHasher() const
{
    return hasher_;
}

}