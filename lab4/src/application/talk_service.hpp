#pragma once

#include <vector>
#include <memory>
#include <optional>

#include <docs/definitions/talks.hpp>
#include <application/user_service.hpp>
#include <domain/talk.hpp>

namespace lab4::application {

class ITalkRepository {
public:
    virtual ~ITalkRepository() = default;

    virtual std::shared_ptr<lab4::domain::Talk> Add(std::shared_ptr<lab4::domain::Talk> talk) = 0;
    virtual std::optional<std::shared_ptr<lab4::domain::Talk>> Get(lab4::domain::TalkId talkId) const = 0;
    virtual std::vector<std::shared_ptr<lab4::domain::Talk>> Find(domain::EventId eventId) const = 0;
    virtual std::shared_ptr<lab4::domain::Talk> Update(std::shared_ptr<lab4::domain::Talk> talk, domain::EventId eventId) = 0;
    virtual std::vector<std::shared_ptr<lab4::domain::Talk>> GetAll() const = 0;
};

class TalkService {
public:
    explicit TalkService(
        std::shared_ptr<ITalkRepository> talkRepo,
        std::shared_ptr<IUserRepository> userRepo) 
        : talkRepo_(talkRepo), userRepo_(userRepo) {}
    
    lab4::talks::Talk CreateTalk(const lab4::talks::CreateTalkRequestBody& talkDto);
    std::vector<lab4::talks::Talk> GetTalks();

private:
    std::shared_ptr<ITalkRepository> talkRepo_;
    std::shared_ptr<IUserRepository> userRepo_;
};

} // namespace lab4::application
