#pragma once

#include <application/talk_service.hpp>
#include <userver/storages/postgres/cluster.hpp>

namespace lab3::infrastructure {

class PostgresTalkRepository final : public lab3::application::ITalkRepository {
public:
    explicit PostgresTalkRepository(userver::storages::postgres::ClusterPtr cluster);

    std::shared_ptr<lab3::domain::Talk> Add(std::shared_ptr<lab3::domain::Talk> talk) override;
    std::optional<std::shared_ptr<lab3::domain::Talk>> Get(lab3::domain::TalkId talkId) const override;
    std::vector<std::shared_ptr<lab3::domain::Talk>> Find(domain::EventId eventId) const override;
    std::shared_ptr<lab3::domain::Talk> Update(std::shared_ptr<lab3::domain::Talk> talk, domain::EventId eventId) override;
    std::vector<std::shared_ptr<lab3::domain::Talk>> GetAll() const override;

private:
    userver::storages::postgres::ClusterPtr cluster_;
};

}  // namespace lab3::infrastructure
