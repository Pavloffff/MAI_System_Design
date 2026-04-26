#include <infrastructure/components/talk_repository.hpp>
#include <infrastructure/mongo/talk_repository.hpp>

#include <cstdlib>

#include <userver/components/component_context.hpp>

namespace lab4::infrastructure {

TalkRepositoryComponent::TalkRepositoryComponent(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : LoggableComponentBase(config, context)
{
    const char* mongo_uri_env = std::getenv("MONGO_URI");
    const std::string mongo_uri = mongo_uri_env ? std::string{mongo_uri_env}
                                                : "mongodb://mongo:mongo@mongo:27017/conference_db?authSource=admin";
    talkRepo_ = std::make_shared<lab4::infrastructure::MongoTalkRepository>(
        mongo_uri);
}

std::shared_ptr<lab4::application::ITalkRepository> TalkRepositoryComponent::GetRepository() const
{
    return talkRepo_;
}

}