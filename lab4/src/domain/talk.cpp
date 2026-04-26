#include <domain/talk.hpp>

namespace lab4::domain {

bool Talk::CheckTimeInterval() const 
{ 
    return start_ < end_; 
}

void Talk::SetId(TalkId id) 
{ 
    this->id_ = id; 
}

TalkId Talk::GetId() const { return id_; }

const std::string& Talk::GetTitle() const { return title_; }

const std::optional<std::string>& Talk::GetDescription() const 
{
  return description_;
}

std::chrono::system_clock::time_point Talk::GetStart() const 
{ 
    return start_; 
}

std::chrono::system_clock::time_point Talk::GetEnd() const 
{ 
    return end_; 
}

UserId Talk::GetUserId() const { return userId_; }

EventId Talk::GetEventId() const { return eventId_; }

void Talk::SetEventId(EventId eventId)
{
    eventId_ = eventId;
}

}  // namespace lab4::domain
