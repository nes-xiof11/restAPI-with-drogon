#include "seeder.hpp"
#include "../service/user.hpp"
#include "../models/user.hpp"
#include "../models/model.hpp"

void misc::seeder(const Json::Value &config) 
{
    static auto storage = model::get_storage();
    static auto service = service::user(storage);
    auto admin = model::user::from_json(config["admin"]);

    if (service.create(admin) != -1) {
        LOG(INFO) << "User Admin was created successfuly";
        return;
    }
    LOG(WARNING) << "User Admin was not created";
}