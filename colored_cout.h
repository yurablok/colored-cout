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
#include <cstdint>

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

#if defined(_WIN32)
enum class clr : uint8_t {
    __FOREGROUND_BLUE      = 0x0001,
    __FOREGROUND_GREEN     = 0x0002,
    __FOREGROUND_RED       = 0x0004,
    __FOREGROUND_INTENSITY = 0x0008,
    __BACKGROUND_BLUE      = 0x0010,
    __BACKGROUND_GREEN     = 0x0020,
    __BACKGROUND_RED       = 0x0040,
    __BACKGROUND_INTENSITY = 0x0080,

    grey        = __FOREGROUND_BLUE  | __FOREGROUND_GREEN | __FOREGROUND_RED,
    blue        = __FOREGROUND_BLUE  | __FOREGROUND_INTENSITY,
    green       = __FOREGROUND_GREEN | __FOREGROUND_INTENSITY,
    cyan        = __FOREGROUND_BLUE  | __FOREGROUND_GREEN | __FOREGROUND_INTENSITY,
    red         = __FOREGROUND_RED   | __FOREGROUND_INTENSITY,
    magenta     = __FOREGROUND_BLUE  | __FOREGROUND_RED   | __FOREGROUND_INTENSITY,
    yellow      = __FOREGROUND_GREEN | __FOREGROUND_RED   | __FOREGROUND_INTENSITY,
    white       = __FOREGROUND_BLUE  | __FOREGROUND_GREEN | __FOREGROUND_RED | __FOREGROUND_INTENSITY,
    on_blue     = __BACKGROUND_BLUE,//| __BACKGROUND_INTENSITY
    on_red      = __BACKGROUND_RED,//| __BACKGROUND_INTENSITY
    on_magenta  = __BACKGROUND_BLUE  | __BACKGROUND_RED,//| __BACKGROUND_INTENSITY
    on_grey     = __BACKGROUND_BLUE  | __BACKGROUND_GREEN | __BACKGROUND_RED,
    on_green    = __BACKGROUND_GREEN | __BACKGROUND_INTENSITY,
    on_cyan     = __BACKGROUND_BLUE  | __BACKGROUND_GREEN | __BACKGROUND_INTENSITY,
    on_yellow   = __BACKGROUND_GREEN | __BACKGROUND_RED   | __BACKGROUND_INTENSITY,
    on_white    = __BACKGROUND_BLUE  | __BACKGROUND_GREEN | __BACKGROUND_RED | __BACKGROUND_INTENSITY,
    reset       = 0xFF,
};
#elif defined(__unix__) || defined(__APPLE__)
enum class clr : uint8_t {
    grey       = 30,
    red        = 31,
    green      = 32,
    yellow     = 33,
    blue       = 34,
    magenta    = 35,
    cyan       = 36,
    white      = 37,
    on_grey    = 40,
    on_red     = 41,
    on_green   = 42,
    on_yellow  = 43,
    on_blue    = 44,
    on_magenta = 45,
    on_cyan    = 46,
    on_white   = 47,
    reset
};
#else
#   error unsupported
#endif


#if defined(_WIN32)
namespace colored_cout_impl {
# ifndef WINBASEAPI
extern "C" {
    struct CONSOLE_SCREEN_BUFFER_INFO {
        int16_t dwSize_X, dwSize_Y;
        int16_t dwCursorPosition_X, dwCursorPosition_Y;
        uint16_t wAttributes;
        int16_t srWindow_Left, srWindow_Top, srWindow_Right, srWindow_Bottom;
        int16_t dwMaximumWindowSize_X, dwMaximumWindowSize_Y;
    };
    static_assert(sizeof(CONSOLE_SCREEN_BUFFER_INFO) == 22, "");

    extern void* __stdcall GetStdHandle(uint32_t nStdHandle);
    extern int32_t __stdcall GetConsoleScreenBufferInfo(void* hConsoleOutput,
        CONSOLE_SCREEN_BUFFER_INFO* lpConsoleScreenBufferInfo);
    extern int32_t __stdcall SetConsoleTextAttribute(void* hConsoleOutput, uint32_t wAttributes);
} // extern "C"
# endif // WINADVAPI

    inline uint16_t getConsoleTextAttr() {
#     ifndef WINBASEAPI
        constexpr uint32_t STD_OUTPUT_HANDLE = -11;
#     endif // WINBASEAPI
        CONSOLE_SCREEN_BUFFER_INFO buffer_info;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &buffer_info);
        return buffer_info.wAttributes;
    }
    inline void setConsoleTextAttr(const uint16_t attr) {
#     ifndef WINBASEAPI
        constexpr uint32_t STD_OUTPUT_HANDLE = -11;
#     endif // WINBASEAPI
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attr);
    }
} // namespace colored_cout_impl
#endif

template <typename type>
type& operator<<(type& ostream, const clr color) {
# if defined(_WIN32)
    //static const uint16_t initial_attributes = colored_cout_impl::getConsoleTextAttr();
    static const uint16_t initial_attributes = static_cast<uint16_t>(clr::grey);
    static uint16_t background = initial_attributes & 0x00F0;
    static uint16_t foreground = initial_attributes & 0x000F;
# endif
    if (color == clr::reset) {
#     if defined(_WIN32)
        ostream.flush();
        colored_cout_impl::setConsoleTextAttr(initial_attributes);
        background = initial_attributes & 0x00F0;
        foreground = initial_attributes & 0x000F;
#     elif defined(__unix__) || defined(__APPLE__)
        ostream << "\033[m";
#     endif
    }
    else {
#     if defined(_WIN32)
        uint16_t set = 0;
        const uint16_t colorCode = static_cast<uint16_t>(color);
        if (colorCode & 0x00F0) {
            background = colorCode;
            set = background | foreground;
        }
        else if (colorCode & 0x000F) {
            foreground = colorCode;
            set = background | foreground;
        }
        ostream.flush();
        colored_cout_impl::setConsoleTextAttr(set);
#     elif defined(__unix__) || defined(__APPLE__)
        ostream << "\033[" << static_cast<uint32_t>(color) << "m";
#     endif
    }
    return ostream;
}
