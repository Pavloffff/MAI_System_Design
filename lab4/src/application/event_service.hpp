#pragma once

#include <vector>
#include <memory>
#include <optional>

#include <docs/definitions/events.hpp>
#include <application/talk_service.hpp>

namespace lab4::application {

class IEventRepository {
public:
    virtual ~IEventRepository() = default;

    virtual std::shared_ptr<lab4::domain::Event> Add(std::shared_ptr<lab4::domain::Event> event) = 0;
    virtual std::optional<std::shared_ptr<lab4::domain::Event>> Get(lab4::domain::EventId eventId) const = 0;
};

class EventService {
public:
    explicit EventService(
        std::shared_ptr<IEventRepository> eventRepo,
        std::shared_ptr<ITalkRepository> talkRepo,
        std::shared_ptr<IUserRepository> userRepo)
        : eventRepo_(eventRepo), talkRepo_(talkRepo), userRepo_(userRepo) {}
    lab4::events::Event CreateEvent(lab4::events::CreateEventRequestBody eventDto);
    lab4::talks::Talk AddTalkToEvent(lab4::domain::EventId eventId, lab4::domain::TalkId talkId, lab4::domain::UserId userId);
    std::vector<lab4::talks::Talk> GetEventTalks(lab4::domain::EventId eventId);

private:
    bool CheckScheduleIntersects_(const lab4::domain::Event& event, const lab4::domain::Talk& talk) const;
    std::shared_ptr<IEventRepository> eventRepo_;
    std::shared_ptr<ITalkRepository> talkRepo_;
    std::shared_ptr<IUserRepository> userRepo_;
};

}