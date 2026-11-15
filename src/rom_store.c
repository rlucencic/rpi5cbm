#include <stdio.h>
#include <string.h>
#include "emu/emu.h"
#include "rom_store.h"

static const struct {
    const char *name;
    uint32_t size;
} roms[ROM_COUNT] = {
    { "c64basic.rom", 8192 }, { "c64kernal.rom", 8192 }, { "c64chargen.rom", 4096 },
    { "1541.rom", 16384 }, { "c128basic.rom", 32768 }, { "c128kernal.rom", 16384 },
    { "c128chargen.rom", 8192 }, { "c128c64.rom", 16384 }, { "1571.rom", 32768 },
};

const char *rom_store_name(rom_id_t id)
{
    return id < ROM_COUNT ? roms[id].name : "";
}

uint32_t rom_store_size(rom_id_t id)
{
    return id < ROM_COUNT ? roms[id].size : 0;
}

/* Not erased, not zeros: something at the start of most 4 KB blocks (the
 * 1571's ROM has one that starts with $FF bytes)
 */
static bool plausible(const uint8_t *p, uint32_t size)
{
    int blank = 0, blocks = 0;
    for (uint32_t off = 0; off < size; off += 4096, blocks++) {
        bool ff = true, zero = true;
        for (int i = 0; i < 64; i++) {
            ff &= p[off + i] == 0xFF;
            zero &= p[off + i] == 0x00;
        }
        blank += ff || zero;
    }
    return blank * 4 <= blocks;
}

bool rom_store_load(rom_id_t id, uint8_t *buf)
{
    if (id >= ROM_COUNT) {
        return false;
    }
    uint32_t size = roms[id].size;
    return emu_rom_read(roms[id].name, buf, size) == (long)size && plausible(buf, size);
}
