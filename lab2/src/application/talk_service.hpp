#pragma once

#include <vector>
#include <memory>
#include <optional>

#include <docs/definitions/talks.hpp>
#include "domain/talk.hpp"

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
        std::shared_ptr<ITalkRepository> talkRepo) : talkRepo_(talkRepo) {}
    
    lab2::talks::Talk CreateTalk(const lab2::talks::CreateTalkRequestBody& userDto);
    std::vector<lab2::talks::Talk> GetTalks();

private:
    std::shared_ptr<ITalkRepository> talkRepo_;
};

} // namespace lab2::application
