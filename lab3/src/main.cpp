#include <userver/clients/dns/component.hpp>
#include <userver/clients/http/component_list.hpp>
#include <userver/components/component.hpp>
#include <userver/components/component_list.hpp>
#include <userver/components/minimal_server_component_list.hpp>
#include <userver/congestion_control/component.hpp>
#include <userver/server/handlers/ping.hpp>
#include <userver/storages/postgres/component.hpp>
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
        lab3::infrastructure::JwtAuthCheckerFactory>();
    auto component_list =
        userver::components::MinimalServerComponentList()
            .Append<userver::server::handlers::Ping>()
            .Append<userver::components::TestsuiteSupport>()
            .AppendComponentList(userver::clients::http::ComponentList())
            .Append<userver::clients::dns::Component>()
            .Append<userver::congestion_control::Component>()
            .Append<userver::components::Postgres>("postgres-db")
            .Append<lab3::interfaces::UserLoginHandler>()
            .Append<lab3::interfaces::UserUserCreateHandler>()
            .Append<lab3::interfaces::UserGetUserHandler>()
            .Append<lab3::interfaces::UserGetUsersHandler>()
            .Append<lab3::interfaces::TalkCreateHandler>()
            .Append<lab3::interfaces::TalkGetAllHandler>()
            .Append<lab3::interfaces::EventAddTalkHandler>()
            .Append<lab3::interfaces::EventGetTalksHandler>()
            .Append<lab3::interfaces::EventCreateHandler>()
            .Append<lab3::application::UserServiceComponent>()
            .Append<lab3::application::TalkServiceComponent>()
            .Append<lab3::application::EventServiceComponent>()
            .Append<lab3::infrastructure::UserRepositoryComponent>()
            .Append<lab3::infrastructure::TalkRepositoryComponent>()
            .Append<lab3::infrastructure::EventRepositoryComponent>()
            .Append<lab3::infrastructure::HasherComponent>()
            .Append<lab3::infrastructure::JwtAuthComponent>();

    return userver::utils::DaemonMain(argc, argv, component_list);
}