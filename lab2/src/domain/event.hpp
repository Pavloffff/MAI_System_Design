#pragma once

#include <string>
#include <cstdint>
#include <regex>
#include <stdexcept>

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

}