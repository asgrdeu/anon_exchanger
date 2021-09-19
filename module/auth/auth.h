//
// Created by Евпатов Михаил on 19.07.2021.
//

#include <string>

#ifndef UNTITLED2_AUTH_DATA_H
#define UNTITLED2_AUTH_DATA_H

struct AuthData {
    std::string login;
    std::string password;
};

AuthData auth();

#endif //UNTITLED2_AUTH_DATA_H
