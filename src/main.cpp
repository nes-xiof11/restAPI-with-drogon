#include "models/model.hpp"
#include "models/user.hpp"
#include "service/user.hpp"

int main(int argc, char** argv) {

    auto storage = model::get_storage();
    service::user user_service(storage);
    model::user created_user =
    {
        .name = "Fernando",
        .nickname = "Azevedo",
        .email = "fernando.azevedo@gmail.com",
        .password = "7272gsya",
    }; 

    user_service.create(created_user);
    auto users = user_service.get_all();
    if (not users.has_value())
        return -1;
    for (auto &user: users.value())
    {   
        std::cout << user.name;
    }
    return 0;
}
