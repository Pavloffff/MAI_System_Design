#pragma once

#include <vector>
#include <memory>
#include <optional>

#include <docs/definitions/users.hpp>
#include <domain/user.hpp>

namespace lab4::application {

class IUserRepository {
public:
    virtual ~IUserRepository() = default;

    virtual std::shared_ptr<lab4::domain::User> Add(std::shared_ptr<lab4::domain::User> user) = 0;
    virtual std::optional<std::shared_ptr<lab4::domain::User>> Get(lab4::domain::UserId userId) const = 0;
    virtual std::vector<std::shared_ptr<lab4::domain::User>> Find(
        const std::optional<lab4::domain::Email>& email,
        const std::optional<std::string>& name,
        const std::optional<std::string>& surname) const = 0;
};

class ITokenRepository {
public:
    virtual ~ITokenRepository() = default;

    virtual std::string Get(std::shared_ptr<lab4::domain::User> user) = 0;
};

class UserService {
public:
    explicit UserService(
        std::shared_ptr<IUserRepository> userRepo,
        std::shared_ptr<ITokenRepository> tokenRepo,
        std::shared_ptr<lab4::domain::IPasswordHasher> hasher)
        : userRepo_(std::move(userRepo)),
          tokenRepo_(std::move(tokenRepo)),
          hasher_(std::move(hasher)) {}

    lab4::users::User CreateUser(const lab4::users::UserCreateRequestBody& userDto);
    std::vector<lab4::users::User> GetUsersByNameAndSurname(
        const std::string& name, const std::string& surname) const;
    lab4::users::UserLoginResponseBody UserLogin(
        const lab4::users::UserLoginRequestBody& loginDto);
    std::optional<lab4::users::User> GetUserByEmail(
        const std::string& email) const;

private:
    std::shared_ptr<IUserRepository> userRepo_;
    std::shared_ptr<ITokenRepository> tokenRepo_;
    std::shared_ptr<lab4::domain::IPasswordHasher> hasher_;
};

} // namespace lab4::application