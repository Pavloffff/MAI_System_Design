#pragma once

#include <memory>
#include <string>

#include <application/user_service.hpp>
#include <infrastructure/jwt/jwt_generator.hpp>

namespace lab3::infrastructure {

class JwtTokenRepository final : public lab3::application::ITokenRepository {
public:
    explicit JwtTokenRepository(
        std::shared_ptr<JwtTokenGenerator> token_generator);

    ~JwtTokenRepository() override = default;

    std::string Get(std::shared_ptr<lab3::domain::User> user) override;

private:
    std::shared_ptr<JwtTokenGenerator> token_generator_;
};

}  // namespace lab3::infrastructure