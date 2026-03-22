#pragma once

#include <memory>
#include <string>

#include <userver/server/handlers/auth/auth_checker_base.hpp>

namespace jwt {

class JwtAuthChecker final : public userver::server::handlers::auth::AuthCheckerBase {
public:
    using AuthCheckResult = userver::server::handlers::auth::AuthCheckResult;

    JwtAuthChecker(const std::string& secret);

    AuthCheckResult CheckAuth(
        const userver::server::http::HttpRequest& request,
        userver::server::request::RequestContext& context) const override;
    bool SupportsUserAuth() const noexcept override { return true; }

private:
    std::string secret_;
};

using JwtAuthCheckerPtr = std::shared_ptr<JwtAuthChecker>;

} // namespace jwt