#include <application/event_service.hpp>
#include <userver/logging/log.hpp>

namespace lab4::application {

lab4::events::Event EventService::CreateEvent(lab4::events::CreateEventRequestBody eventDto)
{
    auto userId = lab4::domain::UserId(eventDto.user_id);
    auto user = userRepo_->Get(userId);
    if (!user.has_value()) {
        throw std::runtime_error("User not found");
    }

    auto event = std::make_shared<lab4::domain::Event>(
        lab4::domain::EventId(0),
        eventDto.title,
        eventDto.private_title,
        eventDto.description,
        eventDto.paid_entrance,
        lab4::domain::EventTypeFromString(lab4::events::ToString(eventDto.event_type)),
        eventDto.registration,
        eventDto.place,
        eventDto.start_time.GetTimePoint(),
        eventDto.end_time.GetTimePoint(),
        userId
    );
    event->CheckTimeInterval();

    event = eventRepo_->Add(event);

    return lab4::events::Event{
        static_cast<int>(event->GetId().Value()),
        event->GetTitle(),
        event->GetPrivateTitle(),
        event->GetDescription(),
        event->GetPaidEntrance(),
        lab4::events::FromString(
            lab4::domain::StringFromEventType(event->GetType()), 
            userver::formats::parse::To<lab4::events::EventType>()),
        event->GetRegistration(),
        event->GetPlace(),
        userver::utils::datetime::TimePointTz(event->GetStart()),
        userver::utils::datetime::TimePointTz(event->GetEnd()),
        static_cast<int>(event->GetUserId().Value())
    };
}

lab4::talks::Talk EventService::AddTalkToEvent(lab4::domain::EventId eventId, lab4::domain::TalkId talkId, lab4::domain::UserId userId)
{
    auto talk = talkRepo_->Get(talkId);
    if (!talk.has_value()) {
        throw std::runtime_error("Talk not found");
    }

    auto event = eventRepo_->Get(eventId);
    if (!event.has_value()) {
        throw std::runtime_error("Event not found");
    }

    if (talk.value()->GetUserId().Value() != userId.Value()) {
        throw std::runtime_error("Wrong user");
    }

    if (!CheckScheduleIntersects_(*event.value(), *talk.value())) {
        throw std::runtime_error("Talks intersects");
    }

    talk = talkRepo_->Update(talk.value(), event.value()->GetId());

    return lab4::talks::Talk{
        static_cast<int>(talk.value()->GetId().Value()),
        talk.value()->GetTitle(),
        talk.value()->GetDescription(),
        userver::utils::datetime::TimePointTz(talk.value()->GetStart()),
        userver::utils::datetime::TimePointTz(talk.value()->GetEnd()),
        static_cast<int>(talk.value()->GetUserId().Value()),
        static_cast<int>(talk.value()->GetEventId().Value())
    };
}

std::vector<lab4::talks::Talk> EventService::GetEventTalks(lab4::domain::EventId eventId)
{
    std::vector<lab4::talks::Talk> result;

    auto event = eventRepo_->Get(eventId);
    if (!event.has_value()) {
        throw std::runtime_error("Event not found");
    }

    auto talks = talkRepo_->Find(event.value()->GetId());
    for (auto talk : talks) {
        result.push_back(lab4::talks::Talk{
            static_cast<int>(talk->GetId().Value()),
            talk->GetTitle(),
            talk->GetDescription(),
            userver::utils::datetime::TimePointTz(talk->GetStart()),
            userver::utils::datetime::TimePointTz(talk->GetEnd()),
            static_cast<int>(talk->GetUserId().Value()),
            static_cast<int>(talk->GetEventId().Value())
        });
    }

    return result;
}

bool EventService::CheckScheduleIntersects_(const lab4::domain::Event& event, const lab4::domain::Talk& talk) const
{
    if (talk.GetStart() < event.GetStart() || talk.GetEnd() > event.GetEnd()) {
        return false;
    }

    auto eventTalks = talkRepo_->Find(event.GetId());

    LOG_INFO() << "SIZE : " << eventTalks.size();

    for (const auto& eventTalk : eventTalks) {
        if (talk.GetStart() < eventTalk->GetEnd() && eventTalk->GetStart() < talk.GetEnd()) {
            return false;
        }
    }

    return true;
}

}