#include <fstream>
#include <string>
#include <Windows.h>

const std::string OPTION_FILE_NAME = "vlc_cmd_option.txt";

std::string GetCurrentDirectory()
{
    //Copy paste from https://gist.github.com/karolisjan/f9b8ac3ae2d41ec0ce70f2feac6bdfaf
    //Thank you very much, karolisjan
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");

    return std::string(buffer).substr(0, pos);
}

int main(int argc, char** argv)
{
    //read first line of config file, seem stupid but make the job done.
    std::ifstream f_config;
    const std::string f_config_path = GetCurrentDirectory() + "\\" + OPTION_FILE_NAME;
    f_config.open(f_config_path.c_str());
    std::string arg_string;
    std::getline(f_config, arg_string, '\0');

    if (f_config.is_open()) {
        f_config.close();
    }

    // if the config file is not found then set default command to open vlc2
    if (arg_string.size() == 0) {
        arg_string = "start /d \"C:/Program Files/VideoLAN/VLC/\" vlc2.exe";
    }

    LPWSTR cmd = GetCommandLine(); //get full command without losing quotes
    int l = strlen(argv[0]); // length of first argument without quotes
    cmd = cmd + l + 2; //2 accounted for double quote in GetCommandLineA

    // type conversion and concatinating strings to a full command
    std::wstring w = cmd;
    std::string cmd_str = arg_string + std::string(w.begin(), w.end());

    //execute command
    system(cmd_str.c_str());

    return 0;
}