#pragma once

#include <chrono>
#include <cstdint>
#include <string>

#include <bsoncxx/document/view.hpp>
#include <bsoncxx/types.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/database.hpp>
#include <mongocxx/uri.hpp>

#include <application/talk_service.hpp>

namespace lab4::infrastructure {

class MongoTalkRepository final : public lab4::application::ITalkRepository {
public:
    explicit MongoTalkRepository(std::string mongo_uri);

    std::shared_ptr<lab4::domain::Talk> Add(std::shared_ptr<lab4::domain::Talk> talk) override;
    std::optional<std::shared_ptr<lab4::domain::Talk>> Get(lab4::domain::TalkId talkId) const override;
    std::vector<std::shared_ptr<lab4::domain::Talk>> Find(domain::EventId eventId) const override;
    std::shared_ptr<lab4::domain::Talk> Update(std::shared_ptr<lab4::domain::Talk> talk, domain::EventId eventId) override;
    std::vector<std::shared_ptr<lab4::domain::Talk>> GetAll() const override;

private:
    std::int64_t NextId_() const;
    std::shared_ptr<lab4::domain::Talk> DocumentToTalk_(const bsoncxx::document::view& doc) const;
    static bsoncxx::types::b_date TimePointToBsonDate_(const std::chrono::system_clock::time_point& tp);
    static std::chrono::system_clock::time_point BsonDateToTimePoint_(const bsoncxx::types::b_date& date);

    mongocxx::client client_;
    mongocxx::database db_;
};

}  // namespace lab4::infrastructure
