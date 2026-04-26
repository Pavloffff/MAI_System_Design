#pragma once

#include <mongocxx/instance.hpp>

namespace lab4::infrastructure {

mongocxx::instance& GetMongoInstance();

}  // namespace lab4::infrastructure
