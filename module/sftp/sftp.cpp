//
// Created by Евпатов Михаил on 30.07.2021.
//

#include "sftp.h"

bool sftp::find_local(const std::string& path) {
    return system(("./ftest " + path).c_str());
}

bool sftp::put(const std::string& lpath, const std::string& rpath) {
    return system(("./fput anon-file-browser 192.168.3.4 " + lpath + " " + rpath).c_str());
}
