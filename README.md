# Helii3DS

A homebrew port of Helii from the Nintendo Wii to the Nintendo 3DS.

## Build

You'll need the following to be installed properly:

* devkitPro
* libctru
* libsf2d
* libsfil
* portlibs for 3DS

Then build using:

    make

## Install

Place the files onto your SD card like so:

    3ds
    └── Helii3DS
        ├── img
        │   ├── fire.png
        │   ├── heli.png
        │   └── smoke.png
        ├── Helii3DS.3dsx
        └── Helii3DS.smdh

## Projects used

* devkitPro (homebrew toolchain)
* smea/libctru (3DS core functionality)
* xerpi/libsf2d (for drawing)
* xerpi/libsfil (for image loading)
* libpng (for image decoding)

## Artwork used

* https://openclipart.org/detail/10814/helicopter
* https://openclipart.org/detail/23803/fire

## License

TBD
