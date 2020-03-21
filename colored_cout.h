/*********************************************************************************
 * "colored cout" is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 * 
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * For more information, please refer to:
 * - http://unlicense.org/
 * - https://github.com/yurablok/colored-cout
 ********************************************************************************/
#pragma once
#include <iostream>

#ifdef _WIN32
#   define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#   define NOMINMAX // Fixes the conflicts with STL
#   include <Windows.h>
#   include <wincon.h>
#endif

// usage:
// std::cout << clr::red     << " red "
//           << clr::yellow  << " yellow "
//           << clr::green   << " green "
//           << clr::cyan    << " cyan "
//           << clr::blue    << " blue "
//           << clr::magenta << " magenta "
//           << clr::grey    << " grey "
//           << clr::white   << " white "
//           << clr::reset   << " reset\n";
// std::cout << clr::red     << clr::on_cyan    << " red "
//           << clr::yellow  << clr::on_blue    << " yellow "
//           << clr::green   << clr::on_magenta << " green "
//           << clr::cyan    << clr::on_red     << " cyan "
//           << clr::blue    << clr::on_yellow  << " blue "
//           << clr::magenta << clr::on_green   << " magenta "
//           << clr::grey    << clr::on_white   << " grey "
//           << clr::white   << clr::on_grey    << " white "
//           << clr::reset                      << " reset\n";

#ifdef _WIN32
enum class clr : uint16_t {
      grey       = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED
    , blue       = FOREGROUND_BLUE | FOREGROUND_INTENSITY
    , green      = FOREGROUND_GREEN | FOREGROUND_INTENSITY
    , cyan       = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY
    , red        = FOREGROUND_RED | FOREGROUND_INTENSITY
    , magenta    = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY
    , yellow     = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY
    , white      = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY
    , on_blue    = BACKGROUND_BLUE //| BACKGROUND_INTENSITY
    , on_red     = BACKGROUND_RED //| BACKGROUND_INTENSITY
    , on_magenta = BACKGROUND_BLUE | BACKGROUND_RED //| BACKGROUND_INTENSITY
    , on_grey    = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED
    , on_green   = BACKGROUND_GREEN | BACKGROUND_INTENSITY
    , on_cyan    = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY
    , on_yellow  = BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY
    , on_white   = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY
    , reset
#elif __unix__
enum class clr : uint8_t {
      grey       = 30
    , red        = 31
    , green      = 32
    , yellow     = 33
    , blue       = 34
    , magenta    = 35
    , cyan       = 36
    , white      = 37
    , on_grey    = 40
    , on_red     = 41
    , on_green   = 42
    , on_yellow  = 43
    , on_blue    = 44
    , on_magenta = 45
    , on_cyan    = 46
    , on_white   = 47
    , reset
#else
#   error unsupported
#endif
};

template <typename type>
type& operator<<(type& ostream, const clr color) {
#ifdef _WIN32
    static const uint16_t initial_attributes = [] {
        CONSOLE_SCREEN_BUFFER_INFO buffer_info;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &buffer_info);
        return buffer_info.wAttributes;
    }();
    static uint16_t background = initial_attributes & 0x00F0;
    static uint16_t foreground = initial_attributes & 0x000F;
#endif
    if (color == clr::reset) {
#ifdef _WIN32
        ostream.flush();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), initial_attributes);
#elif __unix__
        ostream << "\033[m";
#endif
    }
    else {
#ifdef _WIN32
        uint16_t set = 0;
        if (static_cast<uint16_t>(color) & 0x00F0) {
            background = static_cast<uint16_t>(color);
            set = background | foreground;
        }
        else if (static_cast<uint16_t>(color) & 0x000F) {
            foreground = static_cast<uint16_t>(color);
            set = background | foreground;
        }
        ostream.flush();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), set);
#elif __unix__
        ostream << "\033[" << static_cast<uint32_t>(color) << "m";
#endif
    }
    return ostream;
}
