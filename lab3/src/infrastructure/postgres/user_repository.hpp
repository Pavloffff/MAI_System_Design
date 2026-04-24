#pragma once

#include <application/user_service.hpp>
#include <userver/storages/postgres/cluster.hpp>

namespace lab3::infrastructure {

class PostgresUserRepository final : public lab3::application::IUserRepository {
public:
    explicit PostgresUserRepository(userver::storages::postgres::ClusterPtr cluster);

    std::shared_ptr<lab3::domain::User> Add(std::shared_ptr<lab3::domain::User> user) override;
    std::optional<std::shared_ptr<lab3::domain::User>> Get(lab3::domain::UserId userId) const override;
    std::vector<std::shared_ptr<lab3::domain::User>> Find(
        const std::optional<lab3::domain::Email>& email,
        const std::optional<std::string>& name,
        const std::optional<std::string>& surname) const override;

private:
    userver::storages::postgres::ClusterPtr cluster_;
};

}  // namespace lab3::infrastructure
