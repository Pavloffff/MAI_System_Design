#include <interfaces/rest/users/users_handler.hpp>

#include <infrastructure/jwt/jwt.hpp>
#include <infrastructure/jwt/jwt_token_repository.hpp>
#include <infrastructure/in_memory/user_repository.hpp>
#include <infrastructure/ssl/password_hasher.hpp>
#include <userver/formats/json/value_builder.hpp>
#include <userver/server/handlers/exceptions.hpp>
#include <application/user_component.hpp>

namespace lab2::interfaces {

UserLoginHandler::UserLoginHandler(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : HttpHandlerBase(config, context),
    userService_(context.FindComponent<lab2::application::UserServiceComponent>().GetService()) 
{
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

UserUserCreateHandler::UserUserCreateHandler(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : HttpHandlerBase(config, context),
    userService_(context.FindComponent<lab2::application::UserServiceComponent>().GetService())
{
}

std::string UserUserCreateHandler::HandleRequestThrow(
    const userver::server::http::HttpRequest& request,
    userver::server::request::RequestContext& context) const
{
    request.GetHttpResponse().SetContentType(userver::http::content_type::kApplicationJson);

    auto requestJson = userver::formats::json::FromString(request.RequestBody());
    auto userCreateDto = requestJson.As<users::UserCreateRequestBody>();

    auto response = userService_->CreateUser(userCreateDto);

    userver::formats::json::ValueBuilder responseJson(response);
    return userver::formats::json::ToString(responseJson.ExtractValue());
}

}  // namespace lab2::interfaces