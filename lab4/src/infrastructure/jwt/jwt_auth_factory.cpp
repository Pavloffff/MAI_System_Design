#include <infrastructure/jwt/jwt_auth_factory.hpp>

namespace lab4::infrastructure {

JwtAuthCheckerFactory::JwtAuthCheckerFactory(
    const userver::components::ComponentContext& context)
    : component_(context.FindComponent<JwtAuthComponent>()) {}

userver::server::handlers::auth::AuthCheckerBasePtr
JwtAuthCheckerFactory::MakeAuthChecker(
    const userver::server::handlers::auth::HandlerAuthConfig&) const {

    return component_.GetChecker();
}

}  // namespace lab4::infrastructure