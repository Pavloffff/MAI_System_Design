#pragma once

#include <domain/user.hpp>
#include <string>
#include <stdexcept>
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>

namespace lab2::infrastructure {

class SslPasswordHasher : public domain::IPasswordHasher {
public:
    std::string Hash(const std::string& raw) const override;

    bool Verify(const std::string& raw, const std::string& hash) const override;
};

}  // namespace lab2::infrastructure