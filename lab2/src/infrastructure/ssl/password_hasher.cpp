#include <infrastructure/ssl/password_hasher.hpp>

namespace lab2::infrastructure {

std::string SslPasswordHasher::Hash(const std::string& raw) const {
    if (raw.empty()) {
        throw std::invalid_argument("Password cannot be empty");
    }

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(raw.data()), raw.size(), hash);

    std::ostringstream oss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return oss.str();
}

bool SslPasswordHasher::Verify(const std::string& raw, const std::string& hash) const {
    return Hash(raw) == hash;
}

}  // namespace lab2::infrastructure