#include <infrastructure/mongo/talk_repository.hpp>

#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>
#include <bsoncxx/types.hpp>
#include <mongocxx/options/find.hpp>
#include <mongocxx/options/find_one_and_update.hpp>

#include <infrastructure/mongo/mongo_instance.hpp>

namespace lab4::infrastructure {

namespace {

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_document;

constexpr std::string_view kDefaultDbName = "conference_db";
constexpr std::string_view kTalksCollection = "talks";
constexpr std::string_view kCountersCollection = "counters";

mongocxx::client CreateClient(const std::string& uri) {
    (void)GetMongoInstance();
    return mongocxx::client{mongocxx::uri{uri}};
}

}  // namespace

MongoTalkRepository::MongoTalkRepository(std::string mongo_uri)
    : client_(CreateClient(mongo_uri)) {
    mongocxx::uri uri(mongo_uri);
    const auto db_name = uri.database().empty() ? std::string{kDefaultDbName} : uri.database();
    db_ = client_[db_name];
}

std::int64_t MongoTalkRepository::NextId_() const {
    auto counters = db_[kCountersCollection.data()];
    mongocxx::options::find_one_and_update opts;
    opts.return_document(mongocxx::options::return_document::k_after);
    opts.upsert(true);

    auto result = counters.find_one_and_update(
        make_document(kvp("_id", "talks")),
        make_document(kvp("$inc", make_document(kvp("seq", 1)))),
        opts);

    if (!result) throw std::runtime_error("Failed to generate next talk id");

    const auto seq = (*result)["seq"];
    if (seq.type() == bsoncxx::type::k_int64) return seq.get_int64().value;
    if (seq.type() == bsoncxx::type::k_int32) return seq.get_int32().value;
    throw std::runtime_error("Invalid counter type for talks.seq");
}

std::shared_ptr<lab4::domain::Talk> MongoTalkRepository::Add(std::shared_ptr<lab4::domain::Talk> talk) {
    auto talks = db_[kTalksCollection.data()];
    const auto next_id = NextId_();

    bsoncxx::builder::basic::document doc_builder;
    doc_builder.append(kvp("id", next_id));
    doc_builder.append(kvp("title", talk->GetTitle()));
    if (talk->GetDescription()) {
        doc_builder.append(kvp("description", *talk->GetDescription()));
    } else {
        doc_builder.append(kvp("description", bsoncxx::types::b_null{}));
    }
    doc_builder.append(kvp("start_time", TimePointToBsonDate_(talk->GetStart())));
    doc_builder.append(kvp("end_time", TimePointToBsonDate_(talk->GetEnd())));
    doc_builder.append(kvp("user_id", talk->GetUserId().Value()));
    doc_builder.append(kvp("event_id", talk->GetEventId().Value()));

    talks.insert_one(doc_builder.view());
    talk->SetId(lab4::domain::TalkId(next_id));
    return talk;
}

std::optional<std::shared_ptr<lab4::domain::Talk>> MongoTalkRepository::Get(lab4::domain::TalkId talkId) const {
    auto talks = db_[kTalksCollection.data()];
    auto result = talks.find_one(make_document(kvp("id", talkId.Value())));
    if (!result) return std::nullopt;
    return DocumentToTalk_(result->view());
}

std::vector<std::shared_ptr<lab4::domain::Talk>> MongoTalkRepository::Find(domain::EventId eventId) const {
    auto talks = db_[kTalksCollection.data()];
    mongocxx::options::find opts;
    opts.sort(make_document(kvp("start_time", 1)));

    std::vector<std::shared_ptr<lab4::domain::Talk>> result;
    for (auto&& doc : talks.find(make_document(kvp("event_id", eventId.Value())), opts)) {
        result.push_back(DocumentToTalk_(doc));
    }
    return result;
}

std::shared_ptr<lab4::domain::Talk> MongoTalkRepository::Update(
    std::shared_ptr<lab4::domain::Talk> talk, domain::EventId eventId) {
    auto talks = db_[kTalksCollection.data()];
    auto result = talks.find_one_and_update(
        make_document(kvp("id", talk->GetId().Value())),
        make_document(kvp("$set", make_document(kvp("event_id", eventId.Value())))));

    if (!result) throw std::runtime_error("Talk not found");
    talk->SetEventId(eventId);
    return talk;
}

std::vector<std::shared_ptr<lab4::domain::Talk>> MongoTalkRepository::GetAll() const {
    auto talks = db_[kTalksCollection.data()];
    mongocxx::options::find opts;
    opts.sort(make_document(kvp("id", 1)));

    std::vector<std::shared_ptr<lab4::domain::Talk>> result;
    for (auto&& doc : talks.find({}, opts)) {
        result.push_back(DocumentToTalk_(doc));
    }
    return result;
}

std::shared_ptr<lab4::domain::Talk> MongoTalkRepository::DocumentToTalk_(
    const bsoncxx::document::view& doc) const {
    std::optional<std::string> description = std::nullopt;
    if (const auto desc = doc["description"]; desc && desc.type() == bsoncxx::type::k_string) {
        description = std::string(desc.get_string().value);
    }

    return std::make_shared<lab4::domain::Talk>(
        lab4::domain::TalkId(doc["id"].get_int64().value),
        std::string(doc["title"].get_string().value),
        description,
        BsonDateToTimePoint_(doc["start_time"].get_date()),
        BsonDateToTimePoint_(doc["end_time"].get_date()),
        lab4::domain::UserId(doc["user_id"].get_int64().value),
        lab4::domain::EventId(doc["event_id"].get_int64().value));
}

bsoncxx::types::b_date MongoTalkRepository::TimePointToBsonDate_(
    const std::chrono::system_clock::time_point& tp) {
    return bsoncxx::types::b_date{
        std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch())};
}

std::chrono::system_clock::time_point MongoTalkRepository::BsonDateToTimePoint_(
    const bsoncxx::types::b_date& date) {
    return std::chrono::system_clock::time_point{
        std::chrono::milliseconds{date.to_int64()}};
}

}  // namespace lab4::infrastructure
