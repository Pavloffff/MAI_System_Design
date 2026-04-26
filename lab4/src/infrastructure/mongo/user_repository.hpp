#pragma once

#include <chrono>
#include <cstdint>
#include <string>

#include <bsoncxx/document/view.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/database.hpp>
#include <mongocxx/uri.hpp>

#include <application/user_service.hpp>

namespace lab4::infrastructure {

class MongoUserRepository final : public lab4::application::IUserRepository {
public:
    explicit MongoUserRepository(std::string mongo_uri);

    std::shared_ptr<lab4::domain::User> Add(std::shared_ptr<lab4::domain::User> user) override;
    std::optional<std::shared_ptr<lab4::domain::User>> Get(lab4::domain::UserId userId) const override;
    std::vector<std::shared_ptr<lab4::domain::User>> Find(
        const std::optional<lab4::domain::Email>& email,
        const std::optional<std::string>& name,
        const std::optional<std::string>& surname) const override;

private:
    std::int64_t NextId_() const;
    std::shared_ptr<lab4::domain::User> DocumentToUser_(const bsoncxx::document::view& doc) const;

    mongocxx::client client_;
    mongocxx::database db_;
};

}  // namespace lab4::infrastructure
