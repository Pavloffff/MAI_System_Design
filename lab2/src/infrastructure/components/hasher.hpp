#pragma once

#include <userver/components/loggable_component_base.hpp>
#include <infrastructure/ssl/password_hasher.hpp>

namespace lab2::infrastructure {

class HasherComponent final : public userver::components::LoggableComponentBase {
public:
    static constexpr std::string_view kName = "ssl-hasher-component";

    HasherComponent(const userver::components::ComponentConfig& config,
                    const userver::components::ComponentContext& context);

    std::shared_ptr<lab2::infrastructure::SslPasswordHasher> GetHasher() const;

private:
    std::shared_ptr<lab2::infrastructure::SslPasswordHasher> hasher_;
};

}