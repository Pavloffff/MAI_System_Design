#include <infrastructure/mongo/user_repository.hpp>

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
constexpr std::string_view kUsersCollection = "users";
constexpr std::string_view kCountersCollection = "counters";

mongocxx::client CreateClient(const std::string& uri) {
    (void)GetMongoInstance();
    return mongocxx::client{mongocxx::uri{uri}};
}

}  // namespace

MongoUserRepository::MongoUserRepository(std::string mongo_uri)
    : client_(CreateClient(mongo_uri)) {
    mongocxx::uri uri(mongo_uri);
    const auto db_name = uri.database().empty() ? std::string{kDefaultDbName} : uri.database();
    db_ = client_[db_name];
}

std::int64_t MongoUserRepository::NextId_() const {
    auto counters = db_[kCountersCollection.data()];
    mongocxx::options::find_one_and_update opts;
    opts.return_document(mongocxx::options::return_document::k_after);
    opts.upsert(true);

    auto result = counters.find_one_and_update(
        make_document(kvp("_id", "users")),
        make_document(kvp("$inc", make_document(kvp("seq", 1)))),
        opts);

    if (!result) throw std::runtime_error("Failed to generate next user id");

    const auto seq = (*result)["seq"];
    if (seq.type() == bsoncxx::type::k_int64) return seq.get_int64().value;
    if (seq.type() == bsoncxx::type::k_int32) return seq.get_int32().value;
    throw std::runtime_error("Invalid counter type for users.seq");
}

std::shared_ptr<lab4::domain::User> MongoUserRepository::Add(std::shared_ptr<lab4::domain::User> user) {
    auto users = db_[kUsersCollection.data()];
    const auto next_id = NextId_();

    auto doc = make_document(
        kvp("id", next_id),
        kvp("email", user->GetEmail().Value()),
        kvp("name", user->GetName()),
        kvp("surname", user->GetSurname()),
        kvp("phone", user->GetPhone().Value()),
        kvp("password_hash", user->GetPasswordHash()));

    users.insert_one(doc.view());
    user->SetId(lab4::domain::UserId(next_id));
    return user;
}

std::optional<std::shared_ptr<lab4::domain::User>> MongoUserRepository::Get(lab4::domain::UserId userId) const {
    auto users = db_[kUsersCollection.data()];
    auto result = users.find_one(make_document(kvp("id", userId.Value())));

    if (!result) return std::nullopt;
    return DocumentToUser_(result->view());
}

std::vector<std::shared_ptr<lab4::domain::User>> MongoUserRepository::Find(
    const std::optional<lab4::domain::Email>& email,
    const std::optional<std::string>& name,
    const std::optional<std::string>& surname) const {
    auto users = db_[kUsersCollection.data()];

    bsoncxx::builder::basic::document filter;
    if (email) filter.append(kvp("email", email->Value()));
    if (name) {
        filter.append(kvp("name", make_document(
            kvp("$regex", "^" + *name),
            kvp("$options", "i"))));
    }
    if (surname) {
        filter.append(kvp("surname", make_document(
            kvp("$regex", "^" + *surname),
            kvp("$options", "i"))));
    }

    std::vector<std::shared_ptr<lab4::domain::User>> result;
    for (auto&& doc : users.find(filter.view())) {
        result.push_back(DocumentToUser_(doc));
    }
    return result;
}

std::shared_ptr<lab4::domain::User> MongoUserRepository::DocumentToUser_(const bsoncxx::document::view& doc) const {
    return std::make_shared<lab4::domain::User>(
        lab4::domain::UserId(doc["id"].get_int64().value),
        lab4::domain::Email(std::string(doc["email"].get_string().value)),
        std::string(doc["name"].get_string().value),
        std::string(doc["surname"].get_string().value),
        lab4::domain::Phone(std::string(doc["phone"].get_string().value)),
        std::string(doc["password_hash"].get_string().value));
}

}  // namespace lab4::infrastructure
