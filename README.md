# rpi5cbm

A Commodore 64 and 128 for the Raspberry Pi 5, in a window of its own:
[esp32cbm](https://github.com/rlucencic/esp32cbm)'s Commodore on the
[rpi5emu](https://github.com/rlucencic/rpi5emu) runtime.

- A cycle-exact 6510 and CIAs, the VIC-II, the SID, real 1541 and 1571
  drives (D64, D71, G64), cartridges (CRT), programs (PRG, T64); the C128's
  80 columns, FAST mode and CP/M (its Z80).
- The setup screen (model, sound, the drives), the web page for the disk
  images, the console, as the rest of the family.

## Building

See [rpi5emu](https://github.com/rlucencic/rpi5emu#building): esp32emu,
rpi5emu, esp32cbm and rpi5cbm cloned side by side, then

```sh
cd rpi5cbm && cmake -S . -B build -G Ninja && cmake --build build
```

## ROMs

In the data folder's `roms/` (`~/rpi5emu/roms`), named as esp32cbm's:
`c64basic.rom`, `c64kernal.rom`, `c64chargen.rom`, `1541.rom`; for the
C128 `c128basic.rom`, `c128kernal.rom`, `c128chargen.rom`, `c128c64.rom`,
`1571.rom`. Not part of this repository.

## Running

```sh
build/rpi5cbm                         # the setup screen first
build/rpi5cbm -S --choice Model=C128  # straight into a C128
build/rpi5cbm game.d64                # with a disk in drive 8
```

Disks, cartridges and programs live in `~/rpi5emu/cbm/`. The keyboard by
position, as VICE maps a PC's: Esc RUN/STOP, Tab CTRL, Ctrl and Alt C=,
Home CLR/HOME, Page Up RESTORE, F1-F8 as the C64's; typing in lowercase
gives the C64's capitals. The numeric keypad is the joystick in port 2
(F11 switches to port 1), F12 makes the cursor keys the joystick too
(Alt fire). The C128's own keys: F9 ESC, F10 HELP, AltGr ALT, Print
Screen 40/80 DISPLAY.

## Licence

MIT.
