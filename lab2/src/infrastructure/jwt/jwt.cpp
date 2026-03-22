#include <userver/yaml_config/merge_schemas.hpp>

#include <infrastructure/jwt/jwt.hpp>

namespace lab2::jwt {

namespace {
static constexpr std::string_view kSecret = "secret";
}

JwtAuthComponent::JwtAuthComponent(
        const userver::components::ComponentConfig& config,
        const userver::components::ComponentContext& context)
        : LoggableComponentBase(config, context) {

    authorizer_ = std::make_shared<JwtAuthChecker>(config[kSecret].As<std::string>());
}

JwtAuthCheckerPtr JwtAuthComponent::Get() const { return authorizer_; }

userver::yaml_config::Schema JwtAuthComponent::GetStaticConfigSchema() {
    return userver::yaml_config::MergeSchemas<LoggableComponentBase>(R"(
type: object
description: JWT Auth Checker Component
additionalProperties: false
properties:
    secret:
        type: string
        description: secret key for JWT validation
)");
}

}