# nwn-linux-tweaks

Small fixes and tweaks for the 1.69 linux version of Neverwinter Nights.

The files are fully self-contained and can be loaded independently. Instructions at the start of the file.

To load multiple libraries, separate them by spaces in LD_PRELOAD:

    LD_PRELOAD=./nwmain-camera-unlock.so ./nwmain-baseclass-unlock.so ./nwmain

# Tweaks

## nwmain-baseclass-unlock

Unlocks additional base class selection at character creation.

## nwmain-camera-unlock

Unlocks the camera angle and distance, and increases the fog rendering distance.

## nwmain-list-modes

Unlocks selection of various resolutions in the in game options menu.

# Binaries

Prebuilt binaries are included in the bin/ folder for your convenience. It is however recommended you build them yourself per the instructions in the source files.

# Other similar projects

[nwmovies](https://github.com/nwnlinux/nwmovies) allows for playing of Bink videos on Linux.

[nwuser](https://github.com/nwnlinux/nwuser) keeps NWN data in the home directory, allowing multiple users to share an installation.

[nwmouse](https://github.com/nwnlinux/nwmouse) enables hardware mouse on Linux, removing stutter.

[nwlogger](https://github.com/nwnlinux/nwlogger) adds additional client side logging to NWN.


# License

All code is released under the [WTFPL-2](http://wtfpl2.com/)
