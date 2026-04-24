#include <infrastructure/postgres/talk_repository.hpp>

#include <chrono>
#include <cstdint>

namespace lab3::infrastructure {

PostgresTalkRepository::PostgresTalkRepository(userver::storages::postgres::ClusterPtr cluster)
    : cluster_(std::move(cluster)) {}

std::shared_ptr<lab3::domain::Talk> PostgresTalkRepository::Add(std::shared_ptr<lab3::domain::Talk> talk) {
    const auto res = cluster_->Execute(
        userver::storages::postgres::ClusterHostType::kMaster,
        "INSERT INTO talks(title, description, start_time, end_time, user_id, event_id) "
        "VALUES($1, $2, $3, $4, $5, $6) RETURNING id",
        talk->GetTitle(),
        talk->GetDescription(),
        talk->GetStart(),
        talk->GetEnd(),
        talk->GetUserId().Value(),
        talk->GetEventId().Value());
    talk->SetId(lab3::domain::TalkId(res.Front()["id"].As<std::int64_t>()));
    return talk;
}

std::optional<std::shared_ptr<lab3::domain::Talk>> PostgresTalkRepository::Get(lab3::domain::TalkId talkId) const {
    const auto res = cluster_->Execute(
        userver::storages::postgres::ClusterHostType::kSlave,
        "SELECT id, title, description, start_time, end_time, user_id, event_id FROM talks WHERE id=$1",
        talkId.Value());
    if (res.IsEmpty()) return std::nullopt;

    const auto row = res.Front();
    return std::make_shared<lab3::domain::Talk>(
        lab3::domain::TalkId(row["id"].As<std::int64_t>()),
        row["title"].As<std::string>(),
        row["description"].As<std::optional<std::string>>(),
        row["start_time"].As<std::chrono::system_clock::time_point>(),
        row["end_time"].As<std::chrono::system_clock::time_point>(),
        lab3::domain::UserId(row["user_id"].As<std::int64_t>()),
        lab3::domain::EventId(row["event_id"].As<std::int64_t>()));
}

std::vector<std::shared_ptr<lab3::domain::Talk>> PostgresTalkRepository::Find(domain::EventId eventId) const {
    std::vector<std::shared_ptr<lab3::domain::Talk>> talks;
    const auto res = cluster_->Execute(
        userver::storages::postgres::ClusterHostType::kSlave,
        "SELECT id, title, description, start_time, end_time, user_id, event_id "
        "FROM talks WHERE event_id=$1 ORDER BY start_time",
        eventId.Value());
    for (const auto& row : res) {
        talks.push_back(std::make_shared<lab3::domain::Talk>(
            lab3::domain::TalkId(row["id"].As<std::int64_t>()),
            row["title"].As<std::string>(),
            row["description"].As<std::optional<std::string>>(),
            row["start_time"].As<std::chrono::system_clock::time_point>(),
            row["end_time"].As<std::chrono::system_clock::time_point>(),
            lab3::domain::UserId(row["user_id"].As<std::int64_t>()),
            lab3::domain::EventId(row["event_id"].As<std::int64_t>())));
    }
    return talks;
}

std::shared_ptr<lab3::domain::Talk> PostgresTalkRepository::Update(
    std::shared_ptr<lab3::domain::Talk> talk, domain::EventId eventId) {
    const auto res = cluster_->Execute(
        userver::storages::postgres::ClusterHostType::kMaster,
        "UPDATE talks SET event_id=$2 WHERE id=$1 RETURNING id",
        talk->GetId().Value(),
        eventId.Value());
    if (res.IsEmpty()) throw std::runtime_error("Talk not found");
    talk->SetEventId(eventId);
    return talk;
}

std::vector<std::shared_ptr<lab3::domain::Talk>> PostgresTalkRepository::GetAll() const {
    std::vector<std::shared_ptr<lab3::domain::Talk>> talks;
    const auto res = cluster_->Execute(
        userver::storages::postgres::ClusterHostType::kSlave,
        "SELECT id, title, description, start_time, end_time, user_id, event_id FROM talks ORDER BY id");
    for (const auto& row : res) {
        talks.push_back(std::make_shared<lab3::domain::Talk>(
            lab3::domain::TalkId(row["id"].As<std::int64_t>()),
            row["title"].As<std::string>(),
            row["description"].As<std::optional<std::string>>(),
            row["start_time"].As<std::chrono::system_clock::time_point>(),
            row["end_time"].As<std::chrono::system_clock::time_point>(),
            lab3::domain::UserId(row["user_id"].As<std::int64_t>()),
            lab3::domain::EventId(row["event_id"].As<std::int64_t>())));
    }
    return talks;
}

}  // namespace lab3::infrastructure
