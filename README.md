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
```

Tested on MSVC 14.0 + Windows 10 & GCC 5.2.1 + Ubuntu 15.10.
