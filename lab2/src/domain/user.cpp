#include <domain/user.hpp>

namespace lab2::domain {

bool User::CheckPassword(const std::string& raw, IPasswordHasher& hasher) const {
    return hasher.Verify(raw, password_hash_);
}

UserId User::Id() const {
    return id_;
}

Email User::GetEmail() const {
    return email_;
}

std::string User::GetName() const {
    return name_;
}

std::string User::GetSurname() const {
    return surname_;
}

Phone User::GetPhone() const {
    return phone_;
}

void User::SetId(UserId id) {
    this->id_ = id;
}


}