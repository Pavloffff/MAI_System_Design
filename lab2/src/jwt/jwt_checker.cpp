#include <jwt-cpp/jwt.h>
#include <userver/http/common_headers.hpp>

#include <jwt/jwt_checker.hpp>

namespace jwt {

namespace {
static constexpr std::string_view kAlgorithm = "Bearer ";
// static constexpr const char* kServiceName = "sample";
}

JwtAuthChecker::JwtAuthChecker(const std::string& secret) : secret_(secret) {}

JwtAuthChecker::AuthCheckResult JwtAuthChecker::CheckAuth(
    const userver::server::http::HttpRequest& request,
    userver::server::request::RequestContext&
) const {
    const std::string_view auth_header = request.GetHeader(userver::http::headers::kAuthorization);
    if (auth_header.empty()) {
        return AuthCheckResult{AuthCheckResult::Status::kTokenNotFound, "Missing 'Authorization' header"};
    }

    if (!auth_header.starts_with(kAlgorithm)) {
        return AuthCheckResult{AuthCheckResult::Status::kInvalidToken, "Invalid authorization type, expected 'Bearer'"};
    }

    const std::string_view token = auth_header.substr(kAlgorithm.length());
    try {
        // TODO: Verify me!
        // (https://github.com/Thalhammer/jwt-cpp/blob/master/example/jwks-verify.cpp)
        return {};

    } catch (const ::jwt::error::token_verification_exception& exc) {
        return AuthCheckResult{
            AuthCheckResult::Status::kInvalidToken,
            "Token verification failed: " + std::string{exc.what()}
        };
    } catch (const std::exception& exc) {
        return AuthCheckResult{
            AuthCheckResult::Status::kForbidden,
            "Token processing error: " + std::string{exc.what()}
        };
    }
}

} // namespace jwt