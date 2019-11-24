font2bytes
========================
![](https://github.com/ayoy/font2bytes/workflows/cmake/badge.svg)

A tribute to [Lucky Resistor](http://luckyresistor.me) and his [FontToBytes](https://github.com/LuckyResistor/FontToBytes) MacOS app. This is a multi-platform port of the app that converts font bitmap to array of bytes for use in embedded systems.
Read the whole story [in my blog post](https://kapusta.cc/2019/02/10/font2bytes/).

Components
-------------------
* **libfont2bytes** - a font conversion library written in plain C++
* **f2b** - a command-line tool in C/C++
* **font2bytes** - an GUI application written in Qt

Requirements
-------------------
* C++17
* CMake and libpng for the command-line tool
* Qt for the GUI app

Building
-------------------
For the GUI app, use FontToBytes-gui.pro:

    $ qmake FontToBytes-gui.pro
    $ make
    $ ./build/font2bytes

For the command-line tool you can use FontToBytes-cli.pro:

    $ qmake FontToBytes-cli.pro
    $ make
    $ ./build/f2b

or if you don't have Qt (or don't want to use `qmake`):

    $ mkdir build && cd build
    $ cmake ..
    $ make
    $ ./f2b

There's a `make install` target provided, if you feel like integrating the app within your operating system (`make uninstall` is present too, also for the CMake build).

Usage
-------------------
See example font files in `templates` directory. You'll also find there PSD templates for 8x8 and 16x11 fonts.

Author
-------------------
Dominik Kapusta http://kapusta.cc


License
-------------------
LGPL v3.0, see LICENSE for details.
