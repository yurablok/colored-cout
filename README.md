# colored cout

![Screen](https://github.com/yurablok/colored-cout/blob/master/sample.png)

"colored cout" is a simple overloading of operator<< that allow you to print in console using 8 basic colors:
- default console color
- red
- green
- blue
- cyan
- magenta
- yellow
- white
- grey

Usage:
```cpp
std::cout << clr::red     << " red "
          << clr::yellow  << " yellow "
          << clr::green   << " green "
          << clr::cyan    << " cyan "
          << clr::blue    << " blue "
          << clr::magenta << " magenta "
          << clr::grey    << " grey "
          << clr::white   << " white "
          << clr::reset   << " reset\n";
std::cout << clr::red     << clr::on_cyan    << " red "
          << clr::yellow  << clr::on_blue    << " yellow "
          << clr::green   << clr::on_magenta << " green "
          << clr::cyan    << clr::on_red     << " cyan "
          << clr::blue    << clr::on_yellow  << " blue "
          << clr::magenta << clr::on_green   << " magenta "
          << clr::grey    << clr::on_white   << " grey "
          << clr::white   << clr::on_grey    << " white "
          << clr::reset                      << " reset\n";
std::cout << CLR_RED    " red "
          << CLR_YELLOW " yellow "
          << CLR_GREEN  " green "
          << CLR_CYAN   " cyan "
          << CLR_BLUE   " blue "
          << CLR_MAGENTA" magenta "
          << CLR_GREY   " grey "
          << CLR_WHITE  " white "
          << CLR_RESET  " reset\n";
std::cout << CLR_RED     CLR_ON_CYAN   " red "
          << CLR_YELLOW  CLR_ON_BLUE   " yellow "
          << CLR_GREEN   CLR_ON_MAGENTA" green "
          << CLR_CYAN    CLR_ON_RED    " cyan "
          << CLR_BLUE    CLR_ON_YELLOW " blue "
          << CLR_MAGENTA CLR_ON_GREEN  " magenta "
          << CLR_GREY    CLR_ON_WHITE  " grey "
          << CLR_WHITE   CLR_ON_GREY   " white "
          << CLR_RESET                 " reset\n";
```

Tested on `MSVC 14.0 + Windows 10`, `GCC 5.2 + Ubuntu 15.10`, `MSVC 19.39 + Windows 11`,
`GCC 12.3 + Ubuntu 22.04 in WSL2`
