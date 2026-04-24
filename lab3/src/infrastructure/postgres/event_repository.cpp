#include <infrastructure/postgres/event_repository.hpp>

#include <chrono>
#include <cstdint>

namespace lab3::infrastructure {

PostgresEventRepository::PostgresEventRepository(userver::storages::postgres::ClusterPtr cluster)
    : cluster_(std::move(cluster)) {}

std::shared_ptr<lab3::domain::Event> PostgresEventRepository::Add(std::shared_ptr<lab3::domain::Event> event) {
    const auto res = cluster_->Execute(
        userver::storages::postgres::ClusterHostType::kMaster,
        "INSERT INTO events(title, private_title, description, paid_entrance, event_type, registration, place, start_time, end_time, user_id) "
        "VALUES($1, $2, $3, $4, $5, $6, $7, $8, $9, $10) RETURNING id",
        event->GetTitle(),
        event->GetPrivateTitle(),
        event->GetDescription(),
        event->GetPaidEntrance(),
        lab3::domain::StringFromEventType(event->GetType()),
        event->GetRegistration(),
        event->GetPlace(),
        event->GetStart(),
        event->GetEnd(),
        event->GetUserId().Value());
    event->SetId(lab3::domain::EventId(res.Front()["id"].As<std::int64_t>()));
    return event;
}

std::optional<std::shared_ptr<lab3::domain::Event>> PostgresEventRepository::Get(lab3::domain::EventId eventId) const {
    const auto res = cluster_->Execute(
        userver::storages::postgres::ClusterHostType::kSlave,
        "SELECT id, title, private_title, description, paid_entrance, event_type, registration, place, start_time, end_time, user_id "
        "FROM events WHERE id=$1",
        eventId.Value());
    if (res.IsEmpty()) return std::nullopt;

    const auto row = res.Front();
    return std::make_shared<lab3::domain::Event>(
        lab3::domain::EventId(row["id"].As<std::int64_t>()),
        row["title"].As<std::string>(),
        row["private_title"].As<std::optional<std::string>>(),
        row["description"].As<std::string>(),
        row["paid_entrance"].As<bool>(),
        lab3::domain::EventTypeFromString(row["event_type"].As<std::string>()),
        row["registration"].As<bool>(),
        row["place"].As<std::string>(),
        row["start_time"].As<std::chrono::system_clock::time_point>(),
        row["end_time"].As<std::chrono::system_clock::time_point>(),
        lab3::domain::UserId(row["user_id"].As<std::int64_t>()));
}

}  // namespace lab3::infrastructure
