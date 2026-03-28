#include <application/user_service.hpp>

namespace lab2::application {

lab2::users::User UserService::CreateUser(
    const lab2::users::UserCreateRequestBody& userDto)
{
    std::string password_hash = hasher_->Hash(userDto.password);

    auto user = std::make_shared<lab2::domain::User>(
        lab2::domain::UserId(0),
        lab2::domain::Email(userDto.email),
        userDto.name,
        userDto.surname,
        lab2::domain::Phone(userDto.phone),
        password_hash
    );

    user = userRepo_->Add(user);

    return lab2::users::User{
        static_cast<int>(user->Id().Value()),
        user->GetEmail().Value(),
        user->GetName(),
        user->GetSurname(),
        user->GetPhone().Value()
    };
}

std::vector<lab2::users::User> UserService::GetUsersByNameAndSurname(
    const std::string& name, const std::string& surname) const
{
    std::vector<lab2::users::User> result;

    auto users = userRepo_->Find(std::nullopt, name, surname);

    for (const auto& user : users) {
        result.push_back(lab2::users::User{
            static_cast<int>(user->Id().Value()),
            user->GetEmail().Value(),
            user->GetName(),
            user->GetSurname(),
            user->GetPhone().Value()
        });
    }

    return result;
}

lab2::users::UserLoginResponseBody UserService::UserLogin(
    const lab2::users::UserLoginRequestBody& loginDto)
{
    auto users = userRepo_->Find(
        lab2::domain::Email(loginDto.email),
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

std::optional<lab2::users::User> UserService::GetUserByEmail(
    const lab2::domain::Email& email) const
{
    auto users = userRepo_->Find(email, std::nullopt, std::nullopt);

    if (users.empty()) {
        return std::nullopt;
    }

    const auto& user = users.front();
    return lab2::users::User{
        static_cast<int>(user->Id().Value()),
        user->GetEmail().Value(),
        user->GetName(),
        user->GetSurname(),
        user->GetPhone().Value()
    };
}

} // namespace lab2::application