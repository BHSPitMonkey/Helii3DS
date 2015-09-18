# Helii3DS

A homebrew port of Helii from the Nintendo Wii to the Nintendo 3DS.

## Download

Builds can be downloaded from the [Releases page](https://github.com/BHSPitMonkey/Helii3DS/releases).

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
* [smea/libctru](https://github.com/smea/libctru) (3DS core functionality)
* [xerpi/libsf2d](https://github.com/xerpi/libsf2d) (for drawing)
* [xerpi/libsfil](https://github.com/xerpi/libsfil) (for image loading)
* libpng (for image decoding)

## Artwork used

* https://openclipart.org/detail/10814/helicopter
* https://openclipart.org/detail/23803/fire
* [Knewave font](https://github.com/theleagueof/knewave), used under the terms of the SIL Open Font License:

        Copyright (c) 2010, Tyler Finck <hello@sursly.com>, with Reserved Font Name: "Knewave".
      
        This Font Software is licensed under the SIL Open Font License, Version 1.1.
        This license is copied below, and is also available with a FAQ at:
        http://scripts.sil.org/OFL
        
        Version 1.1 - 26 February 2007

## License

TBD

