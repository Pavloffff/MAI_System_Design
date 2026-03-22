#pragma once

#include <vector>

#include <docs/definitions/users.hpp>
#include <domain/user.hpp>

namespace lab2::application {

class IUserRepository {
public:
    virtual ~IUserRepository() = default;

    virtual lab2::domain::User Add(lab2::domain::User& user) = 0;
    virtual std::vector<lab2::domain::User> Find(
        const std::optional<lab2::domain::Email>& email,
        const std::optional<std::string>& name,
        const std::optional<std::string>& surname) const = 0;
};

class ITokenRepository {
public:
    virtual ~ITokenRepository() = default;

    virtual std::string Get(const lab2::domain::User& user) = 0;
};

class UserService {
public:
    explicit UserService(
        IUserRepository& userRepo,
        ITokenRepository& tokenRepo,
        lab2::domain::IPasswordHasher& hasher) : 
        userRepo_(userRepo), tokenRepo_(tokenRepo), hasher_(hasher) {}

    lab2::users::User CreateUser(
        const lab2::users::UserCreateRequestBody& userDto);
    std::vector<lab2::users::User> GetUsersByNameAndSurname(
        const std::string& name,
        const std::string& surname) const;
    lab2::users::UserLoginResponseBody UserLogin(
        const lab2::users::UserLoginResponseBody& loginDto);
    std::optional<lab2::users::User> GetUserByEmail(
        const lab2::domain::Email& email) const;

private:
    IUserRepository& userRepo_;
    ITokenRepository& tokenRepo_;
    lab2::domain::IPasswordHasher& hasher_;
};

}