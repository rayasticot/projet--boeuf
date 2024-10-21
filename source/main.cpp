#include <iostream>
#include <fstream>
#include <string>

#include <nds.h>
#include <nf_lib.h>
#include <filesystem.h>
#include <maxmod9.h>

#include "nitrofs/soundbank_info.h"

#include "vector2.hpp"
#include "terraingen.hpp"
#include "player.hpp"


int main(void){
	nitroFSInit(NULL);
	NF_SetRootFolder("NITROFS");
    NF_Set3D(0, 0);
	NF_Set2D(1, 0);
	NF_InitSpriteBuffers();
	NF_Init3dSpriteSys();
	//NF_InitSpriteSys(0);
	//NF_InitSpriteSys(1);
	//NF_InitTiledBgBuffers();
	//NF_InitTiledBgSys(0);
	//NF_InitTiledBgSys(1);
	//NF_InitCmapBuffers();

	//mmInitDefault("maxmod/soundbank.bin");
	//mmLoad(MOD_ONENONE4_OPTI);
	//mmStart(MOD_ONENONE4_OPTI, MM_PLAY_LOOP);

	TerrainGen terrain("terrain/info");
	Player player(0, 0);
	NF_Sort3dSprites();
	NF_Swap3dSpritePriority(0, 16); // TRUC DE MERDE CHANGE SA PLUS TARD

	while(1){
		scanKeys();
		player.update();
		//NF_SpriteOamSet(0);
		//NF_SpriteOamSet(1);
		terrain.update(player.camPosition);

		NF_Draw3dSprites();
		glFlush(0);

		swiWaitForVBlank();

		//oamUpdate(&oamMain);
		//oamUpdate(&oamSub);
	}

    return 0;
}
