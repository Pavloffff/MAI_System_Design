#pragma once

#include <vector>
#include <memory>
#include <optional>

#include <docs/definitions/events.hpp>
#include <application/talk_service.hpp>

namespace lab3::application {

class IEventRepository {
public:
    virtual ~IEventRepository() = default;

    virtual std::shared_ptr<lab3::domain::Event> Add(std::shared_ptr<lab3::domain::Event> event) = 0;
    virtual std::optional<std::shared_ptr<lab3::domain::Event>> Get(lab3::domain::EventId eventId) const = 0;
};

class EventService {
public:
    explicit EventService(
        std::shared_ptr<IEventRepository> eventRepo,
        std::shared_ptr<ITalkRepository> talkRepo,
        std::shared_ptr<IUserRepository> userRepo)
        : eventRepo_(eventRepo), talkRepo_(talkRepo), userRepo_(userRepo) {}
    lab3::events::Event CreateEvent(lab3::events::CreateEventRequestBody eventDto);
    lab3::talks::Talk AddTalkToEvent(lab3::domain::EventId eventId, lab3::domain::TalkId talkId, lab3::domain::UserId userId);
    std::vector<lab3::talks::Talk> GetEventTalks(lab3::domain::EventId eventId);

private:
    bool CheckScheduleIntersects_(const lab3::domain::Event& event, const lab3::domain::Talk& talk) const;
    std::shared_ptr<IEventRepository> eventRepo_;
    std::shared_ptr<ITalkRepository> talkRepo_;
    std::shared_ptr<IUserRepository> userRepo_;
};

}