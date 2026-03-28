#pragma once

#include <application/talk_service.hpp>
#include <infrastructure/in_memory/in_memory_db.hpp>

namespace lab2::infrastructure {

class InMemoryTalkRepository final : public lab2::application::ITalkRepository {
public:
    using Storage = InMemoryDB<lab2::domain::TalkId, std::shared_ptr<lab2::domain::Talk>>;

public:
    InMemoryTalkRepository() = default;
    ~InMemoryTalkRepository() override = default;

    std::shared_ptr<lab2::domain::Talk> Add(std::shared_ptr<lab2::domain::Talk> talk) override;
    std::vector<std::shared_ptr<lab2::domain::Talk>> GetAll() const override;

private:
    static constexpr const char* kTableName = "talks";
    mutable Storage storage_;
    lab2::domain::TalkId nextId_ = lab2::domain::TalkId(0);
};

} // namespace lab2::infrastructure