#include "colored_cout.h"

#ifdef _WIN32
#   define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#   define NOMINMAX // Fixes the conflicts with STL
#   include <Windows.h>
#   include <wincon.h>

uint16_t colored_cout_impl::getColorCode(const clr color) {
    switch (color) {
    case clr::grey:         return FOREGROUND_BLUE  | FOREGROUND_GREEN | FOREGROUND_RED;
    case clr::blue:         return FOREGROUND_BLUE  | FOREGROUND_INTENSITY;
    case clr::green:        return FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    case clr::cyan:         return FOREGROUND_BLUE  | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    case clr::red:          return FOREGROUND_RED   | FOREGROUND_INTENSITY;
    case clr::magenta:      return FOREGROUND_BLUE  | FOREGROUND_RED   | FOREGROUND_INTENSITY;
    case clr::yellow:       return FOREGROUND_GREEN | FOREGROUND_RED   | FOREGROUND_INTENSITY;
    case clr::white:        return FOREGROUND_BLUE  | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
    case clr::on_blue:      return BACKGROUND_BLUE; //| BACKGROUND_INTENSITY
    case clr::on_red:       return BACKGROUND_RED;  //| BACKGROUND_INTENSITY
    case clr::on_magenta:   return BACKGROUND_BLUE  | BACKGROUND_RED;  //| BACKGROUND_INTENSITY
    case clr::on_grey:      return BACKGROUND_BLUE  | BACKGROUND_GREEN | BACKGROUND_RED;
    case clr::on_green:     return BACKGROUND_GREEN | BACKGROUND_INTENSITY;
    case clr::on_cyan:      return BACKGROUND_BLUE  | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
    case clr::on_yellow:    return BACKGROUND_GREEN | BACKGROUND_RED   | BACKGROUND_INTENSITY;
    case clr::on_white:     return BACKGROUND_BLUE  | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;
    case clr::reset:
    default: break;
    }
    return static_cast<uint16_t>(clr::reset);
}

uint16_t colored_cout_impl::getConsoleTextAttr() {
    CONSOLE_SCREEN_BUFFER_INFO buffer_info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &buffer_info);
    return buffer_info.wAttributes;
}

void colored_cout_impl::setConsoleTextAttr(const uint16_t attr) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attr);
}

#endif // _WIN32
