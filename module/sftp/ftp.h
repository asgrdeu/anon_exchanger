//
// Created by Михаил Евпатов on 22.09.2021.
//

#include <cstdio>
#include <cstring>
#include <cerrno>
#include <string>

#include <curl/curl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifdef WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

static size_t read_callback(const char *ptr, size_t size, size_t nmemb, FILE *stream);
bool upload(const std::string& url, const std::string& local_path, const std::string& remote_path, const std::string& upload_us, const std::string& rename_to);
int download(const std::string& id, const std::string& url);
