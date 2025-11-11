# onetap

*A 3 rows and 6 column dactyl manuform keyboard with 5 keys for the thumbs where each key is just one tap away.*

* Keyboard Maintainer: [thun11o](https://github.com/thun11o)
* Hardware Supported: *Pro Micro*
* Hardware Availability: Not for sale

Compiling the firmware (after setting up your build environment):

    qmk compile -kb handwired/onetap -km default

Flashing the firmware:

    qmk flash -kb handwired/onetap -km default -bl avrdude-split-left
    qmk flash -kb handwired/onetap -km default -bl avrdude-split-right

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the tab key on the left half or backslash key on the right half respectively and plug in the keyboard 
* **Physical reset button**: Briefly press the button on the back of the PCB
