#pragma once

#include <vector>
#include <memory>
#include <optional>

#include <docs/definitions/users.hpp>
#include <domain/user.hpp>

namespace lab2::application {

class IUserRepository {
public:
    virtual ~IUserRepository() = default;

    virtual std::shared_ptr<lab2::domain::User> Add(std::shared_ptr<lab2::domain::User> user) = 0;
    virtual std::vector<std::shared_ptr<lab2::domain::User>> Find(
        const std::optional<lab2::domain::Email>& email,
        const std::optional<std::string>& name,
        const std::optional<std::string>& surname) const = 0;
};

class ITokenRepository {
public:
    virtual ~ITokenRepository() = default;

    virtual std::string Get(std::shared_ptr<lab2::domain::User> user) = 0;
};

class UserService {
public:
    explicit UserService(
        std::shared_ptr<IUserRepository> userRepo,
        std::shared_ptr<ITokenRepository> tokenRepo,
        std::shared_ptr<lab2::domain::IPasswordHasher> hasher)
        : userRepo_(std::move(userRepo)),
          tokenRepo_(std::move(tokenRepo)),
          hasher_(std::move(hasher)) {}

    lab2::users::User CreateUser(const lab2::users::UserCreateRequestBody& userDto);
    std::vector<lab2::users::User> GetUsersByNameAndSurname(
        const std::string& name, const std::string& surname) const;
    lab2::users::UserLoginResponseBody UserLogin(
        const lab2::users::UserLoginRequestBody& loginDto);
    std::optional<lab2::users::User> GetUserByEmail(
        const std::string& email) const;

private:
    std::shared_ptr<IUserRepository> userRepo_;
    std::shared_ptr<ITokenRepository> tokenRepo_;
    std::shared_ptr<lab2::domain::IPasswordHasher> hasher_;
};

} // namespace lab2::application