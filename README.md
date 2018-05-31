font2bytes
========================

A tribute to [Lucky Resistor](http://luckyresistor.me) and his [FontToBytes](https://github.com/LuckyResistor/FontToBytes) MacOS app. This is a multi-platform port of the app that converts font bitmap to array of bytes for use in embedded systems.

Components
-------------------

* **libfont2bytes** - a font conversion library written in plain C++
* **f2b** - a command-line tool in C/C++
* **font2bytes** - an GUI application written in Qt


Installation
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

Author
-------------------

Dominik Kapusta http://kapusta.cc


License
-------------------
LGPL v3.0, see LICENSE for details.
