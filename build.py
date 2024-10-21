#!~/env python3

# SPDX-License-Identifier: CC0-1.0
#
# SPDX-FileContributor: Antonio Niño Díaz, 2024

from architectds import *

nitrofs = NitroFS()
#nitrofs.add_grit(['assets/terrain'], 'terrain')
nitrofs_soundbank_header = nitrofs.add_mmutil(['assets/audio'])
nitrofs.add_files_unchanged(['assets/infor'], 'terrain')
#nitrofs.add_grit(['assets/robot'
#nitrofs.add_nitro_engine_md5(['assets/robot'])
#nitrofs.add_nflib_bg_tiled(['assets/bg'], 'bg')
nitrofs.add_nflib_sprite_3d(['assets/terrain'], 'terrain')
nitrofs.add_nflib_sprite_3d(['assets/sprites'], 'sprites')
#nitrofs.add_nflib_font(['assets/fnt'], 'fnt')
nitrofs.generate_image()

arm9 = Arm9Binary(
    sourcedirs=['source'],
    libs=['nflib', 'nds9', 'mm9'],
    libdirs=[
        '${BLOCKSDS}/libs/libnds',
        '${BLOCKSDSEXT}/nflib',
        '${BLOCKSDS}/libs/maxmod'
    ]
)
arm9.add_header_dependencies([nitrofs_soundbank_header])
arm9.generate_elf()

nds = NdsRom(
    binaries=[arm9, nitrofs],
    game_title='NE: NFlib: Template',
)
nds.generate_nds()

nds.run_command_line_arguments()
