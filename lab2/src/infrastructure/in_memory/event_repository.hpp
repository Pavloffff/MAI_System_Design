#pragma once

#include <application/event_service.hpp>
#include <infrastructure/in_memory/in_memory_db.hpp>

namespace lab2::infrastructure {

class InMemoryEventRepository final : public lab2::application::IEventRepository {
public:
    using Storage = InMemoryDB<lab2::domain::EventId, std::shared_ptr<lab2::domain::Event>>;   

public:
    InMemoryEventRepository() = default;
    ~InMemoryEventRepository() override = default;

    std::shared_ptr<lab2::domain::Event> Add(std::shared_ptr<lab2::domain::Event> event) override;
    std::optional<std::shared_ptr<lab2::domain::Event>> Get(lab2::domain::EventId eventId) const override;

private:
    static constexpr const char* kTableName = "events";
    mutable Storage storage_;
    lab2::domain::EventId nextId_ = lab2::domain::EventId(0);
};

}