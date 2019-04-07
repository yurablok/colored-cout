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

Usage:
```cpp
std::cout << clr::red     << "red "
          << clr::yellow  << "yellow "
          << clr::green   << "green "
          << clr::cyan    << "cyan "
          << clr::blue    << "blue "
          << clr::magenta << "magenta\n"
          << clr::reset;
```

Tested on MSVC 14.0 + Windows 10 & GCC 5.2.1 + Ubuntu 15.10.