#include <infrastructure/jwt/jwt_token_repository.hpp>
#include <stdexcept>

namespace lab2::infrastructure {

JwtTokenRepository::JwtTokenRepository(
    std::shared_ptr<JwtTokenGenerator> token_generator)
    : token_generator_(std::move(token_generator))
{
    if (!token_generator_) {
        throw std::invalid_argument("JwtTokenRepository: token_generator is null");
    }
}

std::string JwtTokenRepository::Get(std::shared_ptr<lab2::domain::User> user)
{
    // Получаем строковое представление UserId
    const std::string user_id = std::to_string(user->Id().Value());

    // Генерируем JWT для данного пользователя
    return token_generator_->Generate(user_id);
}

}  // namespace lab2::infrastructure