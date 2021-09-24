// Project created 18.07.2021 by maxfps11, pacific

// Zero part
// File manipulation (generate file hash sum)
//
// First part
// https://www.coveros.com/calling-python-code-from-c/ using python from C/C++
// https://docs.python.org/3/c-api/intro.html?highlight=py_initialize#include-files
// Calling .py scripts for manipulate pysftp
//
// Second part
// https://stackoverflow.com/questions/24386993/calling-shell-script-from-c
// https://habr.com/ru/company/ruvds/blog/325522/
// shell-scripts from C/C++ check installing environment, (build project)*

#include <iostream>
#include <vector>
#include <map>

#include "module/sys/sys.h"
#include "module/sftp/ftp.h"
#include "module/auth/auth.h"

using namespace std;

std::map<std::string, std::string> files_links;
std::map<std::string, std::string> app_config;
std::vector<std::string> files_names;

int main(int argc, char* argv[]) {
    //files_names.emplace_back("fput");
    files_names.emplace_back("config");
    files_names.emplace_back("auth.sh");
    files_names.emplace_back("auth_data.sh");

    cout << "Building files links:\n";
    for (auto & name : files_names) {
        cout << sys::get_file_link(argv[0], name) << endl;
        cout << "\tValidate " + name + " file: ";
        if (sys::is_regular_file(sys::get_file_link(argv[0], name))) {
            cout << "OK\n";

            files_links.emplace(name, sys::get_file_link(argv[0], name));
            cout << "\tBuilding " + name + " file link: "
                << "OK\n";
        }
        else {
            cout << "FAIL\n";
            return 0;
        }
    }

    cout << "Parsing configs:\n"
        << files_links.find("config")->second << endl;
    sys::get_config_params(app_config, files_links.find("config")->second);
    if (!app_config.empty()) {
        for (auto &p : app_config) {
            cout << "\t\t->\t" + p.first << " set to " << p.second << endl;
        }
        cout << "\tApplying configuration parameters: OK\n";
    }
    else {
        cout << "\tFAIL: Configuration file is empty.\n";
        return 0;
    }

    std::string url;
    AuthData ad = auth();

    cout << "Building specify protocol URL...\n";
    if (app_config.find("protocol")->second.empty())
        cout << "\tFAIL: Protocol not specified.\n";
    else if (app_config.find("host")->second.empty())
        cout << "\tFAIL: Host not specified.\n";
    else {
        url = app_config.find("protocol")->second + "://" +
                          ad.login + ":" +
                          ad.password + "@" +
                          app_config.find("host")->second + "/";

        if (app_config.find("port")->second != "none")
            url += ";port=" + app_config.find("port")->second;

        cout << "\tURL built: OK\n";
    }

    std::string buf;
    while (buf != "0") {
        cout << "[1] Upload.\n"
             << "[2] Download.\n"
             << "[0] Exit.\n"
             << "Your choice: ";
        cin >> buf;

        if (buf == "1") {
            string path;
            cout << "Enter filepath: ";
            cin >> path;

            cout << "Check file existence...\n";
            if (!sys::is_regular_file(path)) {
                cout << "\tFAIL: File does not exist.\n";
                return 0;
            }
            cout << "\tCheck existence: OK\n";

            cout << "Uploading the " + path << " file...\n";
            if (!upload(url, path, "/", "none", sys::get_file_sha256sum(path) + sys::get_file_extension(path))) {
                cout << "\nFAIL: Error uploading. Check log.\n";
                return 0;
            }
            cout << "\tFile uploaded: OK\n";
            cout << "\tYour file download id: " << sys::get_file_sha256sum(path) + sys::get_file_extension(path)
                 << endl;
        }

        if (buf == "2") {
            string id;
            cout << "Enter id: ";
            cin >> id;

            download(id, url);
        }
    }
    return 0;
}

// 1. Create the file linkage script
// TODO: DONE (main program released).

// 2. Create the configuration file
//      a. host
//      b. port
// TODO: DONE

// 3. Create the configuration file parsing script
// TODO: DONE

// 4. Create the application check script*
