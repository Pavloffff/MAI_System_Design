#include <infrastructure/components/event_repository.hpp>
#include <infrastructure/mongo/event_repository.hpp>

#include <cstdlib>

#include <userver/components/component_context.hpp>

namespace lab4::infrastructure {

EventRepositoryComponent::EventRepositoryComponent(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : LoggableComponentBase(config, context)
{
    const char* mongo_uri_env = std::getenv("MONGO_URI");
    const std::string mongo_uri = mongo_uri_env ? std::string{mongo_uri_env}
                                                : "mongodb://mongo:mongo@mongo:27017/conference_db?authSource=admin";
    eventRepo_ = std::make_shared<lab4::infrastructure::MongoEventRepository>(
        mongo_uri);
}

std::shared_ptr<lab4::application::IEventRepository> EventRepositoryComponent::GetRepository() const
{
    return eventRepo_;
}

}