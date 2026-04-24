#include <infrastructure/postgres/user_repository.hpp>

#include <cstdint>

namespace lab3::infrastructure {

PostgresUserRepository::PostgresUserRepository(userver::storages::postgres::ClusterPtr cluster)
    : cluster_(std::move(cluster)) {}

std::shared_ptr<lab3::domain::User> PostgresUserRepository::Add(std::shared_ptr<lab3::domain::User> user) {
    const auto res = cluster_->Execute(
        userver::storages::postgres::ClusterHostType::kMaster,
        "INSERT INTO users(email, name, surname, phone, password_hash) VALUES($1, $2, $3, $4, $5) RETURNING id",
        user->GetEmail().Value(),
        user->GetName(),
        user->GetSurname(),
        user->GetPhone().Value(),
        user->GetPasswordHash());
    user->SetId(lab3::domain::UserId(res.Front()["id"].As<std::int64_t>()));
    return user;
}

std::optional<std::shared_ptr<lab3::domain::User>> PostgresUserRepository::Get(lab3::domain::UserId userId) const {
    const auto res = cluster_->Execute(
        userver::storages::postgres::ClusterHostType::kSlave,
        "SELECT id, email, name, surname, phone, password_hash FROM users WHERE id=$1",
        userId.Value());
    if (res.IsEmpty()) return std::nullopt;

    const auto row = res.Front();
    return std::make_shared<lab3::domain::User>(
        lab3::domain::UserId(row["id"].As<std::int64_t>()),
        lab3::domain::Email(row["email"].As<std::string>()),
        row["name"].As<std::string>(),
        row["surname"].As<std::string>(),
        lab3::domain::Phone(row["phone"].As<std::string>()),
        row["password_hash"].As<std::string>());
}

std::vector<std::shared_ptr<lab3::domain::User>> PostgresUserRepository::Find(
    const std::optional<lab3::domain::Email>& email,
    const std::optional<std::string>& name,
    const std::optional<std::string>& surname) const {
    std::vector<std::shared_ptr<lab3::domain::User>> users;
    const auto res = cluster_->Execute(
        userver::storages::postgres::ClusterHostType::kSlave,
        "SELECT id, email, name, surname, phone, password_hash FROM users "
        "WHERE ($1::text IS NULL OR email = $1) "
        "AND ($2::text IS NULL OR name ILIKE $2) "
        "AND ($3::text IS NULL OR surname ILIKE $3) ORDER BY id",
        email ? std::optional<std::string>(email->Value()) : std::nullopt,
        name ? std::optional<std::string>(*name + "%") : std::nullopt,
        surname ? std::optional<std::string>(*surname + "%") : std::nullopt);

    for (const auto& row : res) {
        users.push_back(std::make_shared<lab3::domain::User>(
            lab3::domain::UserId(row["id"].As<std::int64_t>()),
            lab3::domain::Email(row["email"].As<std::string>()),
            row["name"].As<std::string>(),
            row["surname"].As<std::string>(),
            lab3::domain::Phone(row["phone"].As<std::string>()),
            row["password_hash"].As<std::string>()));
    }
    return users;
}

}  // namespace lab3::infrastructure
