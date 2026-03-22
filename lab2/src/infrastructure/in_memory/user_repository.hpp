#pragma once

#include <mutex>
#include <application/user_service.hpp>
#include <domain/user.hpp>
#include <infrastructure/in_memory/in_memory_db.hpp>

namespace lab2::infrastructure {

class InMemoryUserRepository final : public lab2::application::IUserRepository {
public:
    using Storage = InMemoryDB<lab2::domain::UserId, lab2::domain::User>;

public:
    InMemoryUserRepository() = default;
    ~InMemoryUserRepository() override = default;

    lab2::domain::User Add(lab2::domain::User& user) override;
    std::vector<lab2::domain::User> Find(
        const std::optional<lab2::domain::Email>& email,
        const std::optional<std::string>& name,
        const std::optional<std::string>& surname) const override;

private:
    static constexpr const char* kTableName = "users";
    mutable Storage storage_;
    mutable std::mutex mutex_;
    lab2::domain::UserId nextId_ = lab2::domain::UserId(0);
};

}
