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
//
// Third part
// (Adapt the application for Windows, Mac OS and Linux)*

#include <iostream>
#include <vector>
#include <map>

#include "module/sys/sys.h"

using namespace std;

std::map<std::string, std::string> files_links;
std::map<std::string, std::string> app_config;
std::vector<std::string> files_names;

int main(int argc, char* argv[]) {
    files_names.emplace_back("fput");
    files_names.emplace_back("config");

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

    /*string path;
    cout << "Enter filepath: ";
    cin >> path;

    if (!local::find_local(path))
        local::put(path, local::get_file_sha256sum(path) + ".cbp");*/

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
