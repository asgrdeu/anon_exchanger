//
// Created by Евпатов Михаил on 26.07.2021.
//

#include <vector>
#include "sys.h"

std::string sys::get_file_link(const char *argv0, const std::string& path) {
    return std::filesystem::canonical(argv0).parent_path().c_str() + std::string("/") + path;
}

bool sys::is_regular_file(const std::string& path) {
    return std::filesystem::is_regular_file(path);
}

std::string sys::get_file_sha256sum(const std::string &path) {
    FILE* pipe;
    char buff[64] = {0};
    std::string shasum = "null";

    pipe = popen(("shasum -a 256 " + path + " | grep -Eo '^[0-9a-z]+'").c_str(), "r");

    if (fgets(buff, sizeof(buff), pipe)) {
        shasum = buff;
        shasum = shasum.substr(0, shasum.size() - 1);
    }
    pclose(pipe);
    return shasum;
}

void sys::get_config_params(std::map<std::string, std::string> &params_buff, const std::string &path) {
    char buff[64];
    std::vector<std::string> temp;

    FILE* pipe = popen(("cat " + path + " | grep -oE '[a-z0-9]+'").c_str(), "r");

    for (int i = 0; fgets(buff, sizeof(buff), pipe); i++) {
        temp.resize(i + 1);
        temp[i] = buff;
        temp[i] = temp[i].substr(0, temp[i].size() - 1);
    }

    for (int i = 0; i <= temp.size() / 2; i+=2)
        params_buff.emplace(temp[i], temp[i + 1]);

    pclose(pipe);
}
