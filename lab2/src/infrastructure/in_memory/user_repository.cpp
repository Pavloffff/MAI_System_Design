#include <infrastructure/in_memory/user_repository.hpp>

namespace lab2::infrastructure {

std::shared_ptr<lab2::domain::User> InMemoryUserRepository::Add(
    std::shared_ptr<lab2::domain::User> user)
{
    std::lock_guard lock(mutex_);

    user->SetId(nextId_);
    storage_.Insert(kTableName, nextId_, user);
    nextId_++;

    return user;
}

std::vector<std::shared_ptr<lab2::domain::User>> InMemoryUserRepository::Find(
    const std::optional<lab2::domain::Email>& email,
    const std::optional<std::string>& name,
    const std::optional<std::string>& surname) const
{
    std::lock_guard lock(mutex_);
    std::vector<std::shared_ptr<lab2::domain::User>> result;

    auto maybeTable = storage_.TryGetTable(kTableName);
    if (!maybeTable) {
        return result;
    }

    for (const auto& [id, userPtr] : *maybeTable) {
        if (email.has_value() && userPtr->GetEmail() != email) {
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