# onetap

_A 3 rows and 6 column dactyl manuform keyboard with 5 keys for the thumbs where each key is just one tap away._

- Keyboard Maintainer: [thun11o](https://github.com/thun11o)
- Hardware Supported: _Pro Micro_
- Hardware Availability: Not for sale

Compiling the firmware (after setting up your build environment):

    qmk compile -kb handwired/onetap -km default

compile_commands.json is created by passing --compiledb

Flashing the firmware:

    qmk flash -kb handwired/onetap -km default -bl avrdude-split-left
    qmk flash -kb handwired/onetap -km default -bl avrdude-split-right

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

- **Bootmagic reset**: Hold down the tab key on the left half or backslash key on the right half respectively and plug in the keyboard
- **Physical reset button**: Briefly press the button on the back of the PCB

## Special Characters

The keyboard layout is US English but as a German I like to write umlauts or ß and the € when writing in German. For this to function without much overhead
the following must be enabled:

- On Linux select the 'German (US)' keyboad layout with RALT as alternate key
- On MacOS select either 'ABC' or 'US Layout' and switch Command and Option keys
- On Windows select the 'English US International' keyboard layout

Umlauts such as 'ö' can be written by typing 'o' followed by another 'o' within a certain time window (see special_chars.c), otherwise it would keep 'o'.

The mechanism can be toggled by pressing 'q' on the second layer. This can become handy while playing games where if enabled it
would be disruptive as some keystrokes would not be registered.
