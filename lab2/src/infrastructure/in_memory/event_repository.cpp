#include <infrastructure/in_memory/event_repository.hpp>

namespace lab2::infrastructure {

std::shared_ptr<lab2::domain::Event> InMemoryEventRepository::Add(std::shared_ptr<lab2::domain::Event> event)
{
    event->SetId(nextId_);
    storage_.Insert(kTableName, nextId_, event);
    nextId_++;

    return event;
}

std::optional<std::shared_ptr<lab2::domain::Event>> InMemoryEventRepository::Get(lab2::domain::EventId eventId) const
{
    auto maybeTable = storage_.TryGetTable(kTableName);
    if (maybeTable == nullptr) {
        return std::nullopt;
    }

    auto it = maybeTable->find(eventId);
    if (it == maybeTable->end()) {
        return std::nullopt;
    }

    return it->second;
}

}