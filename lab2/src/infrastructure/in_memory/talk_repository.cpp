#include <infrastructure/in_memory/talk_repository.hpp>
#include <userver/logging/log.hpp>

namespace lab2::infrastructure {

std::shared_ptr<lab2::domain::Talk> InMemoryTalkRepository::Add(
    std::shared_ptr<lab2::domain::Talk> talk)
{
    talk->SetId(nextId_);
    storage_.Insert(kTableName, nextId_, talk);
    nextId_++;

    return talk;
}

std::optional<std::shared_ptr<lab2::domain::Talk>> InMemoryTalkRepository::Get(lab2::domain::TalkId talkId) const
{
    auto maybeTable = storage_.TryGetTable(kTableName);
    if (maybeTable == nullptr) {
        return std::nullopt;
    }

    auto it = maybeTable->find(talkId);
    if (it == maybeTable->end()) {
        return std::nullopt;
    }

    return it->second;
}

std::vector<std::shared_ptr<lab2::domain::Talk>> InMemoryTalkRepository::Find(domain::EventId eventId) const
{
    std::vector<std::shared_ptr<lab2::domain::Talk>> result;

    auto maybeTable = storage_.TryGetTable(kTableName);
    if (maybeTable == nullptr) {
        return result;
    }

    for (const auto& [id, talkPtr] : *maybeTable) {
        if (talkPtr->GetEventId().Value() != eventId.Value()) {
            continue;
        }
        
        LOG_INFO() << "ID : " << talkPtr->GetId().Value();

        result.push_back(talkPtr);
    }

    return result;
}

std::shared_ptr<lab2::domain::Talk> InMemoryTalkRepository::Update(std::shared_ptr<lab2::domain::Talk> talk, domain::EventId eventId)
{
    auto maybeTable = storage_.TryGetTable(kTableName);
    if (maybeTable == nullptr) {
        throw std::runtime_error("Talk table not found");
    }

    auto it = maybeTable->find(talk->GetId());
    if (it == maybeTable->end()) {
        throw std::runtime_error("Talk not found");
    }

    it->second->SetEventId(eventId);

    return it->second;
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
