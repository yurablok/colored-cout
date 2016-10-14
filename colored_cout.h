#pragma once

#include <iostream>

#ifdef _WIN32
#   include <Windows.h>
#   include <wincon.h>
#endif

namespace clr
{
// usage:
// std::cout << clr::red     << "red "
//           << clr::yellow  << "yellow "
//           << clr::green   << "green "
//           << clr::cyan    << "cyan "
//           << clr::blue    << "blue "
//           << clr::magenta << "magenta\n"
//           << clr::default_;

#ifdef _WIN32
    enum color
    {
        default_  = 0
        , blue    = FOREGROUND_BLUE | FOREGROUND_INTENSITY
        , green   = FOREGROUND_GREEN | FOREGROUND_INTENSITY
        , cyan    = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY
        , red     = FOREGROUND_RED | FOREGROUND_INTENSITY
        , magenta = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY
        , yellow  = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY
        , white   = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY
    };
#elif __unix__
    enum color
    {
        default_
        , red
        , green
        , yellow
        , blue
        , magenta
        , cyan
        , white
    };
#endif

    namespace internal
    {
#ifdef _WIN32
        static WORD old_color_attrs = -1;
#elif __unix__
        static const char* GetAnsiColorCode(const color &clr)
        {
            switch (clr)
            {
            case clr::default_: return nullptr;
            case clr::red:      return "1";
            case clr::green:    return "2";
            case clr::yellow:   return "3";
            case clr::blue:     return "4";
            case clr::magenta:  return "5";
            case clr::cyan:     return "6";
            case clr::white:    return "7";
            default:            return nullptr;
            }
        }
#endif
    }
}

template <class type>
type& operator<<(type& _Ostr, const clr::color &color)
{
#ifdef _WIN32
    if (clr::internal::old_color_attrs == static_cast<WORD>(-1))
    {
        // Store the current text color
        CONSOLE_SCREEN_BUFFER_INFO buffer_info;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &buffer_info);
        clr::internal::old_color_attrs = buffer_info.wAttributes;
    }
#endif
    if (color == clr::default_)
    {
#ifdef _WIN32
        _Ostr.flush();
        // Restores the text color.
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr::internal::old_color_attrs);
#elif __unix__
        _Ostr << "\033[m";  // Resets the terminal to default
#endif
    }
    else
    {
#ifdef _WIN32
        _Ostr.flush();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(color));
#elif __unix__
        _Ostr << "\033[0;3" << clr::internal::GetAnsiColorCode(color) << "m";
#endif
    }
    return _Ostr;
}
