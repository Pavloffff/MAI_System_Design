#include <infrastructure/in_memory/user_repository.hpp>
#include <userver/logging/log.hpp>

namespace lab2::infrastructure {

std::shared_ptr<lab2::domain::User> InMemoryUserRepository::Add(
    std::shared_ptr<lab2::domain::User> user)
{
    auto maybeTable = storage_.TryGetTable(kTableName);
    if (maybeTable != nullptr) {
        std::vector<std::shared_ptr<lab2::domain::User>> checkUsers;
        for (const auto& [id, userPtr] : *maybeTable) {
            if (userPtr->GetEmail().Value() != user->GetEmail().Value()) {
                continue;
            }

            checkUsers.push_back(userPtr);
        }
        if (checkUsers.size() > 0) {
            throw std::runtime_error("User with this email already exists");
        }
    }

    user->SetId(nextId_);
    storage_.Insert(kTableName, nextId_, user);
    nextId_++;

    return user;
}

std::optional<std::shared_ptr<lab2::domain::User>> InMemoryUserRepository::Get(
    lab2::domain::UserId userId) const
{
    auto maybeTable = storage_.TryGetTable(kTableName);
    if (maybeTable == nullptr) {
        return std::nullopt;
    }

    auto it = maybeTable->find(userId);
    if (it == maybeTable->end()) {
        return std::nullopt;
    }

    return it->second;
}

std::vector<std::shared_ptr<lab2::domain::User>> InMemoryUserRepository::Find(
    const std::optional<lab2::domain::Email>& email,
    const std::optional<std::string>& name,
    const std::optional<std::string>& surname) const
{
    std::vector<std::shared_ptr<lab2::domain::User>> result;

    auto maybeTable = storage_.TryGetTable(kTableName);
    if (maybeTable == nullptr) {
        return result;
    }

    for (const auto& [id, userPtr] : *maybeTable) {
        if (email.has_value() && userPtr->GetEmail().Value() != email->Value()) {
            continue;
        }
        if (name.has_value() && userPtr->GetName() != name) {
            continue;
        }
        if (surname.has_value() && userPtr->GetSurname() != surname) {
            continue;
        }

        result.push_back(userPtr);
    }

    return result;
}

} // namespace lab2::infrastructure