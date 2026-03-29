#include <interfaces/rest/users/users_handler.hpp>

#include <infrastructure/components/jwt.hpp>
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
    try {
        request.GetHttpResponse().SetContentType(userver::http::content_type::kApplicationJson);

        auto requestJson = userver::formats::json::FromString(request.RequestBody());
        auto loginDto = requestJson.As<users::UserLoginRequestBody>();

        auto response = userService_->UserLogin(loginDto);

        userver::formats::json::ValueBuilder responseJson(response);
        return userver::formats::json::ToString(responseJson.ExtractValue());
    } catch (const std::exception& e) {
        LOG_ERROR() << "Failed: " << e.what();

        throw userver::server::handlers::InternalServerError(
            userver::formats::json::MakeObject(
                "message", "Internal server error"
            )
        );
    }
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
    try {

        request.GetHttpResponse().SetContentType(userver::http::content_type::kApplicationJson);
    
        auto requestJson = userver::formats::json::FromString(request.RequestBody());
        auto userCreateDto = requestJson.As<users::UserCreateRequestBody>();
    
        auto response = userService_->CreateUser(userCreateDto);
    
        userver::formats::json::ValueBuilder responseJson(response);
        return userver::formats::json::ToString(responseJson.ExtractValue());
    } catch (const std::exception& e) {
        LOG_ERROR() << "Failed: " << e.what();

        throw userver::server::handlers::InternalServerError(
            userver::formats::json::MakeObject(
                "message", "Internal server error"
            )
        );
    }
}

UserGetUserHandler::UserGetUserHandler(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : HttpHandlerBase(config, context),
    userService_(context.FindComponent<lab2::application::UserServiceComponent>().GetService())
{
}

std::string UserGetUserHandler::HandleRequestThrow(
    const userver::server::http::HttpRequest& request,
    userver::server::request::RequestContext& context) const
{
    try {

        request.GetHttpResponse().SetContentType(userver::http::content_type::kApplicationJson);
    
        const std::string email = request.GetArg("email");
        auto response = userService_->GetUserByEmail(email);
    
        if (response.has_value()) {
            userver::formats::json::ValueBuilder responseJson(*response);
            return userver::formats::json::ToString(responseJson.ExtractValue());
        }
        
        request.SetResponseStatus(userver::server::http::HttpStatus::kNotFound);
        return "{}";
    } catch (const std::exception& e) {
        LOG_ERROR() << "Failed: " << e.what();

        throw userver::server::handlers::InternalServerError(
            userver::formats::json::MakeObject(
                "message", "Internal server error"
            )
        );
    }
}

UserGetUsersHandler::UserGetUsersHandler(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : HttpHandlerBase(config, context),
    userService_(context.FindComponent<lab2::application::UserServiceComponent>().GetService())
{
}

std::string UserGetUsersHandler::HandleRequestThrow(
    const userver::server::http::HttpRequest& request,
    userver::server::request::RequestContext& context) const
{
    try {

        request.GetHttpResponse().SetContentType(userver::http::content_type::kApplicationJson);
    
        const std::string name_surname = request.GetPathArg("name_surname");
        
        LOG_INFO() << "NAME_SURNAME: " << name_surname;
        
        size_t pos = name_surname.find(',');
        std::string name;
        std::string surname;

        if (pos != std::string::npos) {
            name = name_surname.substr(0, pos);
            surname = name_surname.substr(pos + 1);
        } else {
            name = name_surname;
            surname = "";
        }

        LOG_INFO() << "NAME: " << name << " SURNAME: " << surname;

        auto users = userService_->GetUsersByNameAndSurname(name, surname);
        
        userver::formats::json::ValueBuilder itemsBuilder;
        for (auto user : users) {
            userver::formats::json::ValueBuilder userJson(user);
            itemsBuilder.PushBack(userJson.ExtractValue());
        }

        return userver::formats::json::ToString(itemsBuilder.ExtractValue());
    } catch (const std::exception& e) {
        LOG_ERROR() << "Failed: " << e.what();

        throw userver::server::handlers::InternalServerError(
            userver::formats::json::MakeObject(
                "message", "Internal server error"
            )
        );
    }
}

}  // namespace lab2::interfaces