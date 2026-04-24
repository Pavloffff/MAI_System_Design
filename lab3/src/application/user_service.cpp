#include <application/user_service.hpp>
#include <userver/logging/log.hpp>

namespace lab3::application {

lab3::users::User UserService::CreateUser(
    const lab3::users::UserCreateRequestBody& userDto)
{
    std::string password_hash = hasher_->Hash(userDto.password);

    auto user = std::make_shared<lab3::domain::User>(
        lab3::domain::UserId(0),
        lab3::domain::Email(userDto.email),
        userDto.name,
        userDto.surname,
        lab3::domain::Phone(userDto.phone),
        password_hash
    );

    user = userRepo_->Add(user);

    return lab3::users::User{
        static_cast<int>(user->Id().Value()),
        user->GetEmail().Value(),
        user->GetName(),
        user->GetSurname(),
        user->GetPhone().Value()
    };
}

std::vector<lab3::users::User> UserService::GetUsersByNameAndSurname(
    const std::string& name, const std::string& surname) const
{
    std::vector<lab3::users::User> result;

    auto users = userRepo_->Find(std::nullopt, name, surname);

    for (const auto& user : users) {
        result.push_back(lab3::users::User{
            static_cast<int>(user->Id().Value()),
            user->GetEmail().Value(),
            user->GetName(),
            user->GetSurname(),
            user->GetPhone().Value()
        });
    }

    return result;
}

lab3::users::UserLoginResponseBody UserService::UserLogin(
    const lab3::users::UserLoginRequestBody& loginDto)
{
    auto users = userRepo_->Find(
        lab3::domain::Email(loginDto.email),
        std::nullopt,
        std::nullopt
    );

    if (users.empty()) {
        return {false, ""};
    }

    const auto& user = users.front();
    const bool valid = user->CheckPassword(loginDto.password, *hasher_);

    if (!valid) {
        return {false, ""};
    }

    const std::string token = tokenRepo_->Get(user);

    return {true, token};
}

std::optional<lab3::users::User> UserService::GetUserByEmail(
    const std::string& email) const
{
    auto emailDto = domain::Email(email);
    
    auto users = userRepo_->Find(emailDto, std::nullopt, std::nullopt);

    if (users.empty()) {
        return std::nullopt;
    }

    const auto& user = users.front();
    return lab3::users::User{
        static_cast<int>(user->Id().Value()),
        user->GetEmail().Value(),
        user->GetName(),
        user->GetSurname(),
        user->GetPhone().Value()
    };
}

} // namespace lab3::application