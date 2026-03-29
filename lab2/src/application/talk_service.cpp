#include <application/talk_service.hpp>

namespace lab2::application {

lab2::talks::Talk TalkService::CreateTalk(
    const lab2::talks::CreateTalkRequestBody& userDto)
{
    auto talk = std::make_shared<lab2::domain::Talk>(
        lab2::domain::TalkId(0),
        userDto.title,
        userDto.description,
        userDto.start_time.GetTimePoint(),
        userDto.end_time.GetTimePoint(),
        lab2::domain::UserId(userDto.user_id),
        lab2::domain::EventId(userDto.event_id)
    );
    talk->CheckTimeInterval();

    talk = talkRepo_->Add(talk);

    return lab2::talks::Talk{
        static_cast<int>(talk->GetId().Value()),
        talk->GetTitle(),
        talk->GetDescription(),
        userver::utils::datetime::TimePointTz(talk->GetStart()),
        userver::utils::datetime::TimePointTz(talk->GetEnd()),
        static_cast<int>(talk->GetUserId().Value()),
        static_cast<int>(talk->GetEventId().Value())
    };
}

std::vector<lab2::talks::Talk> TalkService::GetTalks()
{
    std::vector<lab2::talks::Talk> result;

    auto talkDtos = talkRepo_->GetAll();

    for (auto talkDto : talkDtos) {
        result.push_back(lab2::talks::Talk(
            talkDto->GetId().Value(),
            talkDto->GetTitle(),
            talkDto->GetDescription(),
            userver::utils::datetime::TimePointTz(talkDto->GetStart()),
            userver::utils::datetime::TimePointTz(talkDto->GetEnd()),
            talkDto->GetUserId().Value(),
            talkDto->GetEventId().Value()
        ));
    }

    return result;
}

}
