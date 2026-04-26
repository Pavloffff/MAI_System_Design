#include <infrastructure/mongo/event_repository.hpp>

#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>
#include <bsoncxx/types.hpp>
#include <mongocxx/options/find_one_and_update.hpp>

#include <infrastructure/mongo/mongo_instance.hpp>

namespace lab4::infrastructure {

namespace {

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_document;

constexpr std::string_view kDefaultDbName = "conference_db";
constexpr std::string_view kEventsCollection = "conferences";
constexpr std::string_view kCountersCollection = "counters";

mongocxx::client CreateClient(const std::string& uri) {
    (void)GetMongoInstance();
    return mongocxx::client{mongocxx::uri{uri}};
}

}  // namespace

MongoEventRepository::MongoEventRepository(std::string mongo_uri)
    : client_(CreateClient(mongo_uri)) {
    mongocxx::uri uri(mongo_uri);
    const auto db_name = uri.database().empty() ? std::string{kDefaultDbName} : uri.database();
    db_ = client_[db_name];
}

std::int64_t MongoEventRepository::NextId_() const {
    auto counters = db_[kCountersCollection.data()];
    mongocxx::options::find_one_and_update opts;
    opts.return_document(mongocxx::options::return_document::k_after);
    opts.upsert(true);

    auto result = counters.find_one_and_update(
        make_document(kvp("_id", "events")),
        make_document(kvp("$inc", make_document(kvp("seq", 1)))),
        opts);

    if (!result) throw std::runtime_error("Failed to generate next event id");

    const auto seq = (*result)["seq"];
    if (seq.type() == bsoncxx::type::k_int64) return seq.get_int64().value;
    if (seq.type() == bsoncxx::type::k_int32) return seq.get_int32().value;
    throw std::runtime_error("Invalid counter type for events.seq");
}

std::shared_ptr<lab4::domain::Event> MongoEventRepository::Add(std::shared_ptr<lab4::domain::Event> event) {
    auto events = db_[kEventsCollection.data()];
    const auto next_id = NextId_();

    bsoncxx::builder::basic::document doc_builder;
    doc_builder.append(kvp("id", next_id));
    doc_builder.append(kvp("title", event->GetTitle()));
    if (event->GetPrivateTitle()) {
        doc_builder.append(kvp("private_title", *event->GetPrivateTitle()));
    } else {
        doc_builder.append(kvp("private_title", bsoncxx::types::b_null{}));
    }
    doc_builder.append(kvp("description", event->GetDescription()));
    doc_builder.append(kvp("paid_entrance", event->GetPaidEntrance()));
    doc_builder.append(kvp("event_type", lab4::domain::StringFromEventType(event->GetType())));
    doc_builder.append(kvp("registration", event->GetRegistration()));
    doc_builder.append(kvp("place", event->GetPlace()));
    doc_builder.append(kvp("start_time", TimePointToBsonDate_(event->GetStart())));
    doc_builder.append(kvp("end_time", TimePointToBsonDate_(event->GetEnd())));
    doc_builder.append(kvp("user_id", event->GetUserId().Value()));

    events.insert_one(doc_builder.view());
    event->SetId(lab4::domain::EventId(next_id));
    return event;
}

std::optional<std::shared_ptr<lab4::domain::Event>> MongoEventRepository::Get(lab4::domain::EventId eventId) const {
    auto events = db_[kEventsCollection.data()];
    auto result = events.find_one(make_document(kvp("id", eventId.Value())));
    if (!result) return std::nullopt;
    return DocumentToEvent_(result->view());
}

std::shared_ptr<lab4::domain::Event> MongoEventRepository::DocumentToEvent_(
    const bsoncxx::document::view& doc) const {
    std::optional<std::string> private_title = std::nullopt;
    if (const auto field = doc["private_title"]; field && field.type() == bsoncxx::type::k_string) {
        private_title = std::string(field.get_string().value);
    }

    return std::make_shared<lab4::domain::Event>(
        lab4::domain::EventId(doc["id"].get_int64().value),
        std::string(doc["title"].get_string().value),
        private_title,
        std::string(doc["description"].get_string().value),
        doc["paid_entrance"].get_bool().value,
        lab4::domain::EventTypeFromString(std::string(doc["event_type"].get_string().value)),
        doc["registration"].get_bool().value,
        std::string(doc["place"].get_string().value),
        BsonDateToTimePoint_(doc["start_time"].get_date()),
        BsonDateToTimePoint_(doc["end_time"].get_date()),
        lab4::domain::UserId(doc["user_id"].get_int64().value));
}

bsoncxx::types::b_date MongoEventRepository::TimePointToBsonDate_(
    const std::chrono::system_clock::time_point& tp) {
    return bsoncxx::types::b_date{
        std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch())};
}

std::chrono::system_clock::time_point MongoEventRepository::BsonDateToTimePoint_(
    const bsoncxx::types::b_date& date) {
    return std::chrono::system_clock::time_point{
        std::chrono::milliseconds{date.to_int64()}};
}

}  // namespace lab4::infrastructure
