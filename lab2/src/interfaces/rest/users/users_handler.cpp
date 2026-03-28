#include <interfaces/rest/users/users_handler.hpp>

#include <application/user_service.hpp>
#include <docs/definitions/users.hpp>
#include <infrastructure/jwt/jwt.hpp>
#include <infrastructure/jwt/jwt_token_repository.hpp>
#include <infrastructure/in_memory/user_repository.hpp>
#include <infrastructure/ssl/password_hasher.hpp>
#include <userver/formats/json/value_builder.hpp>
#include <userver/server/handlers/exceptions.hpp>

namespace lab2::interfaces {

UserLoginHandler::UserLoginHandler(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : HttpHandlerBase(config, context)
{
    const auto& jwt_component =
        context.FindComponent<lab2::infrastructure::JwtAuthComponent>();
    auto generator = jwt_component.GetGenerator();
    auto tokenRepo = std::make_shared<lab2::infrastructure::JwtTokenRepository>(generator);

    auto userRepo = std::make_shared<lab2::infrastructure::InMemoryUserRepository>();
    auto hasher = std::make_shared<lab2::infrastructure::SslPasswordHasher>();

    userService_ = std::make_shared<lab2::application::UserService>(
        userRepo, tokenRepo, hasher
    );
}

std::string UserLoginHandler::HandleRequestThrow(
    const userver::server::http::HttpRequest& request,
    userver::server::request::RequestContext& context) const
{
    request.GetHttpResponse().SetContentType(userver::http::content_type::kApplicationJson);

    auto requestJson = userver::formats::json::FromString(request.RequestBody());
    auto loginDto = requestJson.As<users::UserLoginRequestBody>();

    auto response = userService_->UserLogin(loginDto);

    userver::formats::json::ValueBuilder responseJson(response);
    return userver::formats::json::ToString(responseJson.ExtractValue());
}

}  // namespace lab2::interfaces