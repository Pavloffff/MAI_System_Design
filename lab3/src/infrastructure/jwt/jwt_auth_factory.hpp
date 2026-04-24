#pragma once

#include <userver/server/handlers/auth/auth_checker_factory.hpp>

#include <infrastructure/components/jwt.hpp>

namespace lab3::infrastructure {

class JwtAuthCheckerFactory final
    : public userver::server::handlers::auth::AuthCheckerFactoryBase {
public:
    static constexpr const char* kAuthType = "jwt-auth";

    explicit JwtAuthCheckerFactory(
        const userver::components::ComponentContext& context);

    userver::server::handlers::auth::AuthCheckerBasePtr
    MakeAuthChecker(
        const userver::server::handlers::auth::HandlerAuthConfig&) const override;

private:
    JwtAuthComponent& component_;
};

}  // namespace lab3::infrastructure