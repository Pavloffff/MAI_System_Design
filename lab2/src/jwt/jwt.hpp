#pragma once

#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
#include <userver/components/loggable_component_base.hpp>
#include <userver/yaml_config/schema.hpp>

#include <jwt/jwt_checker.hpp>

namespace jwt {
    
    class JwtAuthComponent final : public userver::components::LoggableComponentBase {
public:
    static constexpr auto kName = "jwt-auth-component";

    JwtAuthComponent(const userver::components::ComponentConfig& config,
                    const userver::components::ComponentContext& context);

    JwtAuthCheckerPtr Get() const;

    static userver::yaml_config::Schema GetStaticConfigSchema();

private:
    JwtAuthCheckerPtr authorizer_;
};

}