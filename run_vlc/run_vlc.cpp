#include <fstream>
#include <string>
// #include <locale>
#include <codecvt>
#include <sstream>
#include <Windows.h>

const std::wstring OPTION_FILE_NAME = L"vlc_cmd_option.txt";

std::wstring GetCurrentDirectory()
{
    //Copy paste from https://gist.github.com/karolisjan/f9b8ac3ae2d41ec0ce70f2feac6bdfaf
    //Thank you very much, karolisjan
    //changed to wstring
    wchar_t buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");

    return std::wstring(buffer).substr(0, pos);
}

int main(int argc, char** argv)
{
    // std::locale::global(std::locale("en_US.utf8"));

    //only read first line of config file, seem stupid but make the job done.
    std::wifstream f_config;
    const std::wstring f_config_path = GetCurrentDirectory() + L"\\" + OPTION_FILE_NAME;
    f_config.open(f_config_path.c_str());
    std::wstring arg_string;
    std::wstringstream wss;
    wss << f_config.rdbuf();
    
    arg_string = wss.str();

    if (f_config.is_open()) {
        f_config.close();
    }

    // if the config file is not found then set default command to open vlc2
    if (arg_string.size() == 0) {
        arg_string = L"start /d \"C:/Program Files/VideoLAN/VLC/\" vlc2.exe";
    }

    LPWSTR cmd = GetCommandLine(); //get full command without losing quotes
    int l = strlen(argv[0]); // length of first argument without quotes
    cmd = cmd + l + 2; //2 accounted for double quote in GetCommandLineA

    // type conversion and concatinating strings to a full command
    std::wstring w = cmd;
    std::wstring cmd_str = arg_string + std::wstring(w.begin(), w.end());

    //execute command
    _wsystem(cmd_str.c_str());

    return 0;
}