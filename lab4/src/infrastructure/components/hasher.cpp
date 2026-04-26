#include <infrastructure/components/hasher.hpp>

namespace lab4::infrastructure {

HasherComponent::HasherComponent(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : LoggableComponentBase(config, context)
{
    hasher_ = std::make_shared<lab4::infrastructure::SslPasswordHasher>();
}

std::shared_ptr<lab4::infrastructure::SslPasswordHasher> HasherComponent::GetHasher() const
{
    return hasher_;
}

}