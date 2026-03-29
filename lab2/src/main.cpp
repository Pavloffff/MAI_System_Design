#include <userver/clients/dns/component.hpp>
#include <userver/clients/http/component_list.hpp>
#include <userver/components/component.hpp>
#include <userver/components/component_list.hpp>
#include <userver/components/minimal_server_component_list.hpp>
#include <userver/congestion_control/component.hpp>
#include <userver/server/handlers/ping.hpp>
#include <userver/server/handlers/tests_control.hpp>
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

int main(int argc, char* argv[]) {
    userver::server::handlers::auth::RegisterAuthCheckerFactory<
        lab2::infrastructure::JwtAuthCheckerFactory>();
    auto component_list =
        userver::components::MinimalServerComponentList()
            .Append<userver::server::handlers::Ping>()
            .Append<userver::components::TestsuiteSupport>()
            .AppendComponentList(userver::clients::http::ComponentList())
            .Append<userver::clients::dns::Component>()
            .Append<userver::server::handlers::TestsControl>()
            .Append<userver::congestion_control::Component>()
            .Append<lab2::interfaces::UserLoginHandler>()
            .Append<lab2::interfaces::UserUserCreateHandler>()
            .Append<lab2::interfaces::UserGetUserHandler>()
            .Append<lab2::interfaces::UserGetUsersHandler>()
            .Append<lab2::interfaces::TalkCreateHandler>()
            .Append<lab2::interfaces::TalkGetAllHandler>()
            .Append<lab2::application::UserServiceComponent>()
            .Append<lab2::application::TalkServiceComponent>()
            .Append<lab2::infrastructure::UserRepositoryComponent>()
            .Append<lab2::infrastructure::TalkRepositoryComponent>()
            .Append<lab2::infrastructure::HasherComponent>()
            .Append<lab2::infrastructure::JwtAuthComponent>();

    return userver::utils::DaemonMain(argc, argv, component_list);
}