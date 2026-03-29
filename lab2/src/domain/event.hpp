#pragma once

#include <optional>
#include <string>
#include <cstdint>
#include <chrono>
#include <regex>
#include <stdexcept>
#include "domain/user.hpp"

namespace lab2::domain {

class EventId {
public:
    explicit EventId(int64_t value) : value_(value) {}

    int64_t Value() const { return value_; }

    bool operator==(const EventId& other) const { return value_ == other.value_; }
    bool operator!=(const EventId& other) const { return !(*this == other); }
    bool operator<(const EventId& other) const { return value_ < other.value_; }
    EventId& operator++() { ++value_; return *this; }
    EventId operator++(int) { EventId old(*this); ++value_; return old; }

private:
    int64_t value_;
};

enum class EventType {
    Public,
    Private
};

inline std::string StringFromEventType(const EventType& value) {
    if (value == EventType::Public) return "public";
    if (value == EventType::Private) return "private";

    throw std::invalid_argument("Invalid string");
}

inline EventType EventTypeFromString(const std::string& value) {
    if (value == "public") return EventType::Public;
    if (value == "private") return EventType::Private;

    throw std::invalid_argument("Invalid EventType: " + value);
}

class Event {
public:
    Event(EventId id, std::string title, std::optional<std::string> privateTitle,
          std::string description, bool paidEntrance, EventType type,
          bool registration, std::string place, std::chrono::system_clock::time_point start,
          std::chrono::system_clock::time_point end, UserId userId)
        : id_(id), title_(std::move(title)), privateTitle_(std::move(privateTitle)),
          description_(std::move(description)), paidEntrance_(paidEntrance),
          type_(std::move(type)), registration_(registration), place_(std::move(place)),
          start_(std::move(start)), end_(std::move(end)), userId_(userId) {}

    bool CheckTimeInterval() const;
    void SetId(EventId id);
    EventId GetId() const;
    const std::string& GetTitle() const;
    const std::optional<std::string>& GetPrivateTitle() const;
    const std::string& GetDescription() const;
    bool GetPaidEntrance() const;
    const EventType& GetType() const;
    bool GetRegistration() const;
    const std::string& GetPlace() const;
    std::chrono::system_clock::time_point GetStart() const;
    std::chrono::system_clock::time_point GetEnd() const;
    UserId GetUserId() const;
    
private:
    EventId id_;
    std::string title_;
    std::optional<std::string> privateTitle_;
    std::string description_;
    bool paidEntrance_ = false;
    EventType type_;
    bool registration_ = false;
    std::string place_;
    std::chrono::system_clock::time_point start_;
    std::chrono::system_clock::time_point end_;
    UserId userId_;
};

}