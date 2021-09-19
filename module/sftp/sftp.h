//
// Created by Евпатов Михаил on 30.07.2021.
//

#ifndef UNTITLED2_SFTP_H
#define UNTITLED2_SFTP_H

#include <string>

namespace sftp {
    // Найти файл по пути
    bool find_local(const std::string& path);

    // Загрузить локальный файл на удаленный хост
    bool put(const std::string& lpath, const std::string& rpath);

    // Поиск файла на сервере по sha256sum
    bool find_remote(const char *sha256sum);

    // Загрузка удаленного файла на локальный хост
    bool get(const char *sha256sum);
};


#endif //UNTITLED2_SFTP_H
