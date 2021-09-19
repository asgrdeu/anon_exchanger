//
// Created by Евпатов Михаил on 19.07.2021.
//

#include "auth.h"

AuthData auth() {
    FILE *pipe;
    char buffer[64];
    AuthData auth_d;

    system("chmod +x ../auth.sh");
    system("chmod +x ../auth_data.sh");
    system("../auth.sh");

    pipe = popen("../auth_data.sh", "r");

    fgets(buffer, sizeof(buffer), pipe);
    auth_d.login = buffer;
    auth_d.login = auth_d.login.substr(0, auth_d.login.size() - 1);

    fgets(buffer, sizeof(buffer), pipe);
    auth_d.password = buffer;
    auth_d.password = auth_d.password.substr(0, auth_d.password.size() - 1);

    pclose(pipe);
    system("rm ./.auth_data");
    return auth_d;
}
