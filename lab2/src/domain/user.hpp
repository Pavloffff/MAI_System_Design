#pragma once

#include <string>
#include <cstdint>
#include <regex>
#include <stdexcept>

namespace lab2::domain {

class UserId {
public:
    explicit UserId(int64_t value) : value_(value) {}

    int64_t Value() const { return value_; }

    bool operator==(const UserId& other) const { return value_ == other.value_; }
    bool operator!=(const UserId& other) const { return !(*this == other); }
    bool operator<(const UserId& other) const { return value_ < other.value_; }
    UserId& operator++() { ++value_; return *this; }
    UserId operator++(int) { UserId old(*this); ++value_; return old; }

private:
    int64_t value_;
};

class Email {
public:
    explicit Email(std::string value) : value_(std::move(value)) {
        if (!IsValid(value_)) {
            throw std::invalid_argument("Invalid email format: " + value_);
        }
    }

    const std::string& Value() const { return value_; }

    bool operator==(const Email& other) const { return value_ == other.value_; }
    bool operator!=(const Email& other) const { return !(*this == other); }

private:
    std::string value_;

    static bool IsValid(const std::string& email) {
        static const std::regex pattern(R"(^[^\s@]+@[^\s@]+\.[^\s@]+$)");
        return std::regex_match(email, pattern);
    }
};

class Phone {
public:
    explicit Phone(std::string value) : value_(std::move(value)) {
        if (!IsValid(value_)) {
            throw std::invalid_argument("Invalid phone format: " + value_);
        }
    }

    const std::string& Value() const { return value_; }

    bool operator==(const Phone& other) const { return value_ == other.value_; }
    bool operator!=(const Phone& other) const { return !(*this == other); }

private:
    std::string value_;

    static bool IsValid(const std::string& email) {
        static const std::regex pattern(R"(^\+\d{1,15}$)");
        return std::regex_match(email, pattern);
    }
};

class IPasswordHasher {
public:
    virtual ~IPasswordHasher() = default;

    virtual std::string Hash(const std::string& raw) const = 0;
    virtual bool Verify(const std::string& raw, const std::string& hash) const = 0;
};

class User {
public:
    User(UserId id, Email email, std::string name, std::string surname,
         Phone phone, std::string password_hash)
        : id_(id), email_(std::move(email)), name_(std::move(name)),
          surname_(std::move(surname)), phone_(std::move(phone)),
          password_hash_(std::move(password_hash)) {}
    
    UserId Id() const;
    Email GetEmail() const;
    std::string GetName() const;
    std::string GetSurname() const;
    Phone GetPhone() const;

    bool CheckPassword(const std::string& raw, IPasswordHasher& hasher) const;
    void SetId(UserId id_);

private:
    UserId id_;
    Email email_;
    std::string name_;
    std::string surname_;
    Phone phone_;
    std::string password_hash_;
};
    
}