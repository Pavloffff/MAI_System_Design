#pragma once

#include <vector>
#include <memory>
#include <optional>

#include <docs/definitions/talks.hpp>
#include <application/user_service.hpp>
#include <domain/talk.hpp>

namespace lab2::application {

class ITalkRepository {
public:
    virtual ~ITalkRepository() = default;

    virtual std::shared_ptr<lab2::domain::Talk> Add(std::shared_ptr<lab2::domain::Talk> talk) = 0;
    virtual std::vector<std::shared_ptr<lab2::domain::Talk>> GetAll() const = 0;
};

class TalkService {
public:
    explicit TalkService(
        std::shared_ptr<ITalkRepository> talkRepo,
        std::shared_ptr<IUserRepository> userRepo) 
        : talkRepo_(talkRepo), userRepo_(userRepo) {}
    
    lab2::talks::Talk CreateTalk(const lab2::talks::CreateTalkRequestBody& talkDto);
    std::vector<lab2::talks::Talk> GetTalks();

private:
    std::shared_ptr<ITalkRepository> talkRepo_;
    std::shared_ptr<IUserRepository> userRepo_;
};

} // namespace lab2::application
