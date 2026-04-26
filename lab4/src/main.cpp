#include <userver/clients/dns/component.hpp>
#include <userver/clients/http/component_list.hpp>
#include <userver/components/component.hpp>
#include <userver/components/component_list.hpp>
#include <userver/components/minimal_server_component_list.hpp>
#include <userver/congestion_control/component.hpp>
#include <userver/server/handlers/ping.hpp>
#include <userver/testsuite/testsuite_support.hpp>
#include <userver/utils/daemon_run.hpp>

#include <infrastructure/jwt/jwt_auth_factory.hpp>
#include <interfaces/rest/users/users_handler.hpp>
#include <interfaces/rest/talks/talks_handler.hpp>
#include <application/user_component.hpp>
#include <application/talk_component.hpp>
#include <infrastructure/components/hasher.hpp>
#include <infrastructure/components/user_repository.hpp>
#include <infrastructure/components/talk_repository.hpp>
#include <infrastructure/components/event_repository.hpp>
#include <application/event_component.hpp>
#include <interfaces/rest/events/events_handler.hpp>

int main(int argc, char* argv[]) {
    userver::server::handlers::auth::RegisterAuthCheckerFactory<
        lab4::infrastructure::JwtAuthCheckerFactory>();
    auto component_list =
        userver::components::MinimalServerComponentList()
            .Append<userver::server::handlers::Ping>()
            .Append<userver::components::TestsuiteSupport>()
            .AppendComponentList(userver::clients::http::ComponentList())
            .Append<userver::clients::dns::Component>()
            .Append<userver::congestion_control::Component>()
            .Append<lab4::interfaces::UserLoginHandler>()
            .Append<lab4::interfaces::UserUserCreateHandler>()
            .Append<lab4::interfaces::UserGetUserHandler>()
            .Append<lab4::interfaces::UserGetUsersHandler>()
            .Append<lab4::interfaces::TalkCreateHandler>()
            .Append<lab4::interfaces::TalkGetAllHandler>()
            .Append<lab4::interfaces::EventAddTalkHandler>()
            .Append<lab4::interfaces::EventGetTalksHandler>()
            .Append<lab4::interfaces::EventCreateHandler>()
            .Append<lab4::application::UserServiceComponent>()
            .Append<lab4::application::TalkServiceComponent>()
            .Append<lab4::application::EventServiceComponent>()
            .Append<lab4::infrastructure::UserRepositoryComponent>()
            .Append<lab4::infrastructure::TalkRepositoryComponent>()
            .Append<lab4::infrastructure::EventRepositoryComponent>()
            .Append<lab4::infrastructure::HasherComponent>()
            .Append<lab4::infrastructure::JwtAuthComponent>();

    return userver::utils::DaemonMain(argc, argv, component_list);
}