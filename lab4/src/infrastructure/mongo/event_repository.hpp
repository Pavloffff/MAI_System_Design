#pragma once

#include <chrono>
#include <cstdint>
#include <string>

#include <bsoncxx/document/view.hpp>
#include <bsoncxx/types.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/database.hpp>
#include <mongocxx/uri.hpp>

#include <application/event_service.hpp>

namespace lab4::infrastructure {

class MongoEventRepository final : public lab4::application::IEventRepository {
public:
    explicit MongoEventRepository(std::string mongo_uri);

    std::shared_ptr<lab4::domain::Event> Add(std::shared_ptr<lab4::domain::Event> event) override;
    std::optional<std::shared_ptr<lab4::domain::Event>> Get(lab4::domain::EventId eventId) const override;

private:
    std::int64_t NextId_() const;
    std::shared_ptr<lab4::domain::Event> DocumentToEvent_(const bsoncxx::document::view& doc) const;
    static bsoncxx::types::b_date TimePointToBsonDate_(const std::chrono::system_clock::time_point& tp);
    static std::chrono::system_clock::time_point BsonDateToTimePoint_(const bsoncxx::types::b_date& date);

    mongocxx::client client_;
    mongocxx::database db_;
};

}  // namespace lab4::infrastructure
