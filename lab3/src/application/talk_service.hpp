#pragma once

#include <vector>
#include <memory>
#include <optional>

#include <docs/definitions/talks.hpp>
#include <application/user_service.hpp>
#include <domain/talk.hpp>

namespace lab3::application {

class ITalkRepository {
public:
    virtual ~ITalkRepository() = default;

    virtual std::shared_ptr<lab3::domain::Talk> Add(std::shared_ptr<lab3::domain::Talk> talk) = 0;
    virtual std::optional<std::shared_ptr<lab3::domain::Talk>> Get(lab3::domain::TalkId talkId) const = 0;
    virtual std::vector<std::shared_ptr<lab3::domain::Talk>> Find(domain::EventId eventId) const = 0;
    virtual std::shared_ptr<lab3::domain::Talk> Update(std::shared_ptr<lab3::domain::Talk> talk, domain::EventId eventId) = 0;
    virtual std::vector<std::shared_ptr<lab3::domain::Talk>> GetAll() const = 0;
};

class TalkService {
public:
    explicit TalkService(
        std::shared_ptr<ITalkRepository> talkRepo,
        std::shared_ptr<IUserRepository> userRepo) 
        : talkRepo_(talkRepo), userRepo_(userRepo) {}
    
    lab3::talks::Talk CreateTalk(const lab3::talks::CreateTalkRequestBody& talkDto);
    std::vector<lab3::talks::Talk> GetTalks();

private:
    std::shared_ptr<ITalkRepository> talkRepo_;
    std::shared_ptr<IUserRepository> userRepo_;
};

} // namespace lab3::application
