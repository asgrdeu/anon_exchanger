//
// Created by Евпатов Михаил on 26.07.2021.
//

#ifndef UNTITLED2_SYS_H
#define UNTITLED2_SYS_H

#include <filesystem>
#include <map>

namespace sys {
    // Return the absolute file link(path) of parent executable directory files.
    std::string get_file_link(const char* argv0, const std::string& path);

    bool is_regular_file(const std::string& path);

    void get_config_params(std::map<std::string, std::string> &params_buff, const std::string& path);

    // Получить sha256sum файла
    std::string get_file_sha256sum(const std::string &path);
}


#endif //UNTITLED2_SYS_H
