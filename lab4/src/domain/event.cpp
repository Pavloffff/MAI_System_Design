#include <domain/event.hpp>

namespace lab4::domain {

bool Event::CheckTimeInterval() const 
{ 
    return start_ < end_; 
}

EventId Event::GetId() const {
    return id_;
}

void Event::SetId(EventId id) {
    id_ = id;
}

const std::string& Event::GetTitle() const {
    return title_;
}

const std::optional<std::string>& Event::GetPrivateTitle() const {
    return privateTitle_;
}

const std::string& Event::GetDescription() const {
    return description_;
}

bool Event::GetPaidEntrance() const {
    return paidEntrance_;
}

const EventType& Event::GetType() const {
    return type_;
}

bool Event::GetRegistration() const {
    return registration_;
}

const std::string& Event::GetPlace() const {
    return place_;
}

std::chrono::system_clock::time_point Event::GetStart() const {
    return start_;
}

std::chrono::system_clock::time_point Event::GetEnd() const {
    return end_;
}

UserId Event::GetUserId() const {
    return userId_;
}

} // namespace lab4::domain