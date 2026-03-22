#include <application/user_service.hpp>

namespace lab2::application {

lab2::users::User UserService::CreateUser(const lab2::users::UserCreateRequestBody& userDto)
{
    std::string password_hash = hasher_.Hash(userDto.password);
    
    lab2::domain::User user(
        lab2::domain::UserId(0),
        lab2::domain::Email(userDto.email),
        userDto.name,
        userDto.surname,
        lab2::domain::Phone(userDto.phone),
        password_hash
    );

    user = userRepo_.Add(user);

    return lab2::users::User{
        static_cast<int>(user.Id().Value()),
        user.GetEmail().Value(),
        user.GetName(),
        user.GetSurname(),
        user.GetPhone().Value()
    };
}

std::vector<lab2::users::User> UserService::GetUsersByNameAndSurname(
    const std::string& name, const std::string& surname) const
{
    std::vector<lab2::users::User> result;

    auto users = userRepo_.Find(
        std::nullopt, name, surname);

    for (auto user : users) {
        result.push_back(lab2::users::User{
        static_cast<int>(user.Id().Value()),
        user.GetEmail().Value(),
        user.GetName(),
        user.GetSurname(),
        user.GetPhone().Value()
        });
    }

    return result;
}

}