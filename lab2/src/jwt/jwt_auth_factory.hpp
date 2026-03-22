#pragma once

#include <userver/server/handlers/auth/auth_checker_factory.hpp>

#include <jwt/jwt_checker.hpp>
#include <jwt/jwt.hpp>

namespace jwt {

class JwtAuthCheckerFactory final : public userver::server::handlers::auth::AuthCheckerFactoryBase {
public:
  static constexpr const char* kAuthType = "jwt-auth";

explicit JwtAuthCheckerFactory(const userver::components::ComponentContext& context);

userver::server::handlers::auth::AuthCheckerBasePtr MakeAuthChecker(const userver::server::handlers::auth::HandlerAuthConfig&) const override;

private:
    jwt::JwtAuthComponent& auth_;
};

}