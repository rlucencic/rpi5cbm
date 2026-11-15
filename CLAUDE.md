# rpi5cbm: the Commodore 64 and 128 on the Raspberry Pi 5

esp32cbm's Commodore (`../esp32cbm/components/cbm`, platform independent)
on the rpi5emu runtime (`../rpi5emu`, its CLAUDE.md: the workflow, the Pi,
the lessons), the 6502 and the C128's Z80 (`CONFIG_Z80_TIMING_TSTATES`,
`CONFIG_Z80_READ_SPECIAL`) esp32emu's. The machine's own behaviour, lessons
and tests are esp32cbm's CLAUDE.md; this project is the glue.

## Layout

| Path | What |
|---|---|
| `src/main.c` | The Commodore as an `emu_machine_t`: esp32cbm's `main/main.c` through `../rpi5emu/tools/port_glue.py` and `port_finish.py` |
| `src/settings.c` | esp32cbm's, over `emu/nvs.h` (section `cbm`: `model`, `joystick`) |
| `src/rom_store.c` | `~/rpi5emu/roms/` through `emu_rom_read()`: c64basic.rom ... 1571.rom |

Keep `src/main.c` in step with esp32cbm's `main/main.c`.

## Build, run, check

```sh
../rpi5emu/tools/pi.sh rpi5cbm build
../rpi5emu/tools/pi.sh rpi5cbm headless     # or run: the window here
../rpi5emu/tools/console.sh i 'T load "$",8\n'
../rpi5emu/tools/pi.sh rpi5cbm shot out.png
```

Console: the runtime's (`h`) and esp32cbm's: `k <n>` tap key n (row * 8 +
column, 1 RETURN), `K <n> 0|1`, `T <text>` (`\n` RETURN; lowercase for the
C64's capitals: capitals come out as graphics), `j <port> <bits>` (1 up 2
down 4 left 8 right 16 fire), `R <model>` restart as 0 C64, 1 C128.

Checked on the Pi (2026-11-15, headless): the C64 at 100% (the emulation
thread ~1% of a core at READY), BASIC typed into; a blank D64 made in
drive 8, a program saved through the real 1541 and the directory listed
(TEST, 663 blocks free), the file in the image after quitting; the C128's
BASIC 7.0. Not yet: the window by hand, sound heard, games, the 1571, the
80 columns, CP/M.
