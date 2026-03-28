#include <infrastructure/in_memory/talk_repository.hpp>

namespace lab2::infrastructure {

std::shared_ptr<lab2::domain::Talk> InMemoryTalkRepository::Add(
    std::shared_ptr<lab2::domain::Talk> talk)
{
    auto maybeTable = storage_.TryGetTable(kTableName);
    if (maybeTable != nullptr) {
        std::vector<std::shared_ptr<lab2::domain::Talk>> checkTalks;
        for (const auto& [id, talkPtr] : *maybeTable) {
            if (talkPtr->GetTitle() != talk->GetTitle()) {
                continue;
            }

            checkTalks.push_back(talkPtr);
        }
        if (checkTalks.size() > 0) {
            throw std::runtime_error("User with this email already exists");
        }
    }

    talk->SetId(nextId_);
    storage_.Insert(kTableName, nextId_, talk);
    nextId_++;

    return talk;
}

std::vector<std::shared_ptr<lab2::domain::Talk>> InMemoryTalkRepository::GetAll() const
{
    std::vector<std::shared_ptr<lab2::domain::Talk>> result;

    auto maybeTable = storage_.TryGetTable(kTableName);
    if (maybeTable == nullptr) {
        return result;
    }

    for (const auto& [id, talkPtr] : *maybeTable) {
        result.push_back(talkPtr);
    }

    return result;
}

}
