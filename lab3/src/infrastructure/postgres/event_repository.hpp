#pragma once

#include <application/event_service.hpp>
#include <userver/storages/postgres/cluster.hpp>

namespace lab3::infrastructure {

class PostgresEventRepository final : public lab3::application::IEventRepository {
public:
    explicit PostgresEventRepository(userver::storages::postgres::ClusterPtr cluster);

    std::shared_ptr<lab3::domain::Event> Add(std::shared_ptr<lab3::domain::Event> event) override;
    std::optional<std::shared_ptr<lab3::domain::Event>> Get(lab3::domain::EventId eventId) const override;

private:
    userver::storages::postgres::ClusterPtr cluster_;
};

}  // namespace lab3::infrastructure
