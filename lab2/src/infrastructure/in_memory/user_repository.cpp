#include <infrastructure/in_memory/user_repository.hpp>

namespace lab2::infrastructure {

lab2::domain::User InMemoryUserRepository::Add(lab2::domain::User& user)
{
    std::lock_guard lock(mutex_);

    user.SetId(nextId_);
    storage_.Insert(kTableName, nextId_, user);
    nextId_++;

    return user;
}

std::vector<lab2::domain::User> InMemoryUserRepository::Find(
    const std::optional<lab2::domain::Email>& email,
    const std::optional<std::string>& name,
    const std::optional<std::string>& surname) const 
{
    std::lock_guard lock(mutex_);
    std::vector<lab2::domain::User> result;
    
    auto maybeTable = storage_.TryGetTable(kTableName);
    if (maybeTable == NULL) {
        return result;
    }

    for (const auto& [id, user] : *maybeTable) {
        if (email.has_value() && user.GetEmail() != email) {
            continue;
        }
        if (name.has_value() && user.GetName() != name) {
            continue;
        }
        if (surname.has_value() && user.GetSurname() != surname) {
            continue;
        }

        result.push_back(user);
    }

    return result;
}


}