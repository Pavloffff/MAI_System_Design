#pragma once

#include <vector>
#include <memory>
#include <optional>

#include <docs/definitions/events.hpp>
#include <application/talk_service.hpp>

namespace lab2::application {

class IEventRepository {
public:
    virtual ~IEventRepository() = default;

    virtual std::shared_ptr<lab2::domain::Event> Add(std::shared_ptr<lab2::domain::Event> event) = 0;
    virtual std::optional<std::shared_ptr<lab2::domain::Event>> Get(lab2::domain::EventId eventId) const = 0;
};

class EventService {
public:
    explicit EventService(
        std::shared_ptr<IEventRepository> eventRepo,
        std::shared_ptr<ITalkRepository> talkRepo,
        std::shared_ptr<IUserRepository> userRepo)
        : eventRepo_(eventRepo), talkRepo_(talkRepo), userRepo_(userRepo) {}
    lab2::events::Event CreateEvent(lab2::events::CreateEventRequestBody eventDto);
    lab2::talks::Talk AddTalkToEvent(lab2::domain::EventId eventId, lab2::domain::TalkId talkId, lab2::domain::UserId userId);
    std::vector<lab2::talks::Talk> GetEventTalks(lab2::domain::EventId eventId);

private:
    bool CheckScheduleIntersects_(const lab2::domain::Event& event, const lab2::domain::Talk& talk) const;
    std::shared_ptr<IEventRepository> eventRepo_;
    std::shared_ptr<ITalkRepository> talkRepo_;
    std::shared_ptr<IUserRepository> userRepo_;
};

}