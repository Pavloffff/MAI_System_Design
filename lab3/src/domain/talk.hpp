#pragma once

#include <string>
#include <cstdint>
#include <chrono>

#include <domain/user.hpp>
#include <domain/event.hpp>

#include <userver/utils/datetime.hpp>

namespace lab3::domain {

class TalkId {
public:
    explicit TalkId(int64_t value) : value_(value) {}

    int64_t Value() const { return value_; }

    bool operator==(const TalkId& other) const { return value_ == other.value_; }
    bool operator!=(const TalkId& other) const { return !(*this == other); }
    bool operator<(const TalkId& other) const { return value_ < other.value_; }
    TalkId& operator++() { ++value_; return *this; }
    TalkId operator++(int) { TalkId old(*this); ++value_; return old; }

private:
    int64_t value_;
};

class Talk {
public:
    Talk(TalkId id, std::string title, std::optional<std::string> description,
         std::chrono::system_clock::time_point start,std::chrono::system_clock::time_point end, 
         UserId userId, EventId eventId)
        : id_(id), title_(std::move(title)), description_(std::move(description)),
          start_(std::move(start)), end_(std::move(end)), userId_(std::move(userId)), 
          eventId_(std::move(eventId)) {}
    
    bool CheckTimeInterval() const;
    void SetId(TalkId id);
    void SetEventId(EventId eventId);
    TalkId GetId() const;
    const std::string& GetTitle() const;
    const std::optional<std::string>& GetDescription() const;
    std::chrono::system_clock::time_point GetStart() const;
    std::chrono::system_clock::time_point GetEnd() const;
    UserId GetUserId() const;
    EventId GetEventId() const;


private:
    TalkId id_;
    std::string title_;
    std::optional<std::string> description_;
    std::chrono::system_clock::time_point start_;
    std::chrono::system_clock::time_point end_;
    UserId userId_;
    EventId eventId_;
};

}