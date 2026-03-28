#pragma once

#include <map>
#include <string>
#include <stdexcept>
#include <optional>

namespace lab2::infrastructure {

template<typename Key, typename Object>
class InMemoryDB {
public:
    using table_type   = std::map<Key, Object>;
    using storage_type = std::map<std::string, table_type>;

public:
    InMemoryDB()  = default;
    ~InMemoryDB() = default;

    void Insert(const std::string& table_name,
                const Key& key,
                const Object& object)
    {
        auto& table = storage_[table_name];

        auto [it, inserted] = table.emplace(key, object);
        if (!inserted) {
            throw std::runtime_error("Insert failed: key already exists");
        }
    }

    void Upsert(const std::string& table_name,
                const Key& key,
                const Object& object)
    {
        storage_[table_name][key] = object;
    }

    Object& Get(const std::string& table_name,
                const Key& key)
    {
        return GetTableOrThrow_(table_name).at(key);
    }

    const Object& Get(const std::string& table_name,
                      const Key& key) const
    {
        return GetTableOrThrow_(table_name).at(key);
    }

    std::optional<Object> TryGet(const std::string& table_name,
                                 const Key& key) const
    {
        auto table_it = storage_.find(table_name);
        if (table_it == storage_.end())
            return std::nullopt;

        const auto& table = table_it->second;
        auto it = table.find(key);
        if (it == table.end())
            return std::nullopt;

        return it->second;
    }

    const table_type* TryGetTable(const std::string& table_name) const
    {
        auto table_it = storage_.find(table_name);
        if (table_it == storage_.end())
            return nullptr;

        return &table_it->second;
    }

    void Remove(const std::string& table_name,
                const Key& key)
    {
        auto table_it = storage_.find(table_name);
        if (table_it == storage_.end())
            return;

        table_it->second.erase(key);
    }

private:
    table_type& GetTableOrThrow_(const std::string& table_name)
    {
        auto it = storage_.find(table_name);
        if (it == storage_.end())
            throw std::runtime_error("Table not found");

        return it->second;
    }

    const table_type& GetTableOrThrow_(const std::string& table_name) const
    {
        auto it = storage_.find(table_name);
        if (it == storage_.end())
            throw std::runtime_error("Table not found");

        return it->second;
    }

private:
    storage_type storage_;
};

}
