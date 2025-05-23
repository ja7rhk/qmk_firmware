# GK87 Q1 Digital Indicator Keyboard

![GK87 Q1 ansi PCBAS](https://i.imgur.com/ckupRBG.jpeg)

## The PCB features:
* QMK & VIA compatibility
* RGB Matrix backlight
* Mechanical switches Keyboard with LED display.


The following is the QMK Firmware for the Desktop 87% keylayout -  designed by Dongguan Jizhi Electronic Technology Co., Ltd

* Keyboard Maintainer: [NaturalZh](https://github.com/NaturalZh)
* Hardware Supported: DesktopPCB for Skyloong keylayout 87%, STM32F103C8T6
* Hardware Availability: [Skyloong CN](http://www.skyloong.com.cn) & [Skyloong HK](https://skyloongtech.com/product-category/keyboards/qmkvia-keyboard/)

Make example for this keyboard (after setting up your build environment):

    make skyloong/gk87/q1/ansi:default

Flashing example for this keyboard:

    make skyloong/gk87/q1/ansi:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
