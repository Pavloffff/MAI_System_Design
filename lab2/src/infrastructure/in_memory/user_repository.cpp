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

            LOG_INFO() << "EMAIL: " << userPtr->GetEmail().Value();

            checkUsers.push_back(userPtr);
        }
        if (checkUsers.size() > 0) {
            throw std::runtime_error("User with this email already exists");
        }
    }

    LOG_INFO() << "TABLE NAME: " << kTableName;

    user->SetId(nextId_);
    LOG_INFO() << "USER " << user->Id().Value() << user->GetEmail().Value();
    storage_.Insert(kTableName, nextId_, user);
    nextId_++;

    return user;
}

std::vector<std::shared_ptr<lab2::domain::User>> InMemoryUserRepository::Find(
    const std::optional<lab2::domain::Email>& email,
    const std::optional<std::string>& name,
    const std::optional<std::string>& surname) const
{
    std::vector<std::shared_ptr<lab2::domain::User>> result;

    LOG_INFO() << "TABLE NAME: " << kTableName;

    auto maybeTable = storage_.TryGetTable(kTableName);
    if (maybeTable == nullptr) {
        return result;
    }
    LOG_INFO() << "TABLE SIZE: " << maybeTable->size();

    for (const auto& [id, userPtr] : *maybeTable) {
        LOG_INFO() << "EMAIL: " << userPtr->GetEmail().Value() << " " << email->Value();
        
        if (email.has_value() && userPtr->GetEmail().Value() != email->Value()) {
            continue;
        }
        if (name.has_value() && userPtr->GetName() != name) {
            continue;
        }
        if (surname.has_value() && userPtr->GetSurname() != surname) {
            continue;
        }

        LOG_INFO() << "EMAIL: " << userPtr->GetEmail().Value();

        result.push_back(userPtr);
    }

    LOG_INFO() << "RESULT SIZE: " << result.size();

    return result;
}

} // namespace lab2::infrastructure