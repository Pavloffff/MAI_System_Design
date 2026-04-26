#include <infrastructure/mongo/mongo_instance.hpp>

namespace lab4::infrastructure {

mongocxx::instance& GetMongoInstance() {
    static mongocxx::instance instance{};
    return instance;
}

}  // namespace lab4::infrastructure
