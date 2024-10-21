#include <iostream>
#include <fstream>
#include <string>

#include <nds.h>
#include <nf_lib.h>

#include "vector2.hpp"
#include "terraingen.hpp"


void TerrainGen::load_textures_and_palettes(std::string filename){
    if(textureLoaded || paletteLoaded || spriteCreated){
        NF_Error(6006, "asd", 4);
    }
    std::ifstream file(filename);
    std::string readText;
    if(!getline(file, readText)){
        NF_Error(6009, "asd", 3);
    }
    if(readText != "_TEX"){
        NF_Error(6000, "asd", 3);
    }
    for(int i = 0; i < TEXTURE_AMMOUNT; i++){
        if(!getline(file, readText)){
            NF_Error(6001, "asd", 3);
        }
        if(readText == "_PAL"){
            NF_Error(6002, "asd", 3);
        }
        NF_LoadSpriteGfx(readText.data(), i, TEXTURE_SIZE, TEXTURE_SIZE);
        NF_Vram3dSpriteGfx(i, i, true);
    }
    getline(file, readText);
    if(readText != "_PAL"){
        NF_Error(6003, "asd", 3);
    }
    for(int i = 0; i < PALETTE_AMMOUNT; i++){
        if(!getline(file, readText)){
            NF_Error(6004, "asd", 3);
        }
        NF_LoadSpritePal(readText.data(), i);
        NF_Vram3dSpritePal(i, i);
    }
    textureLoaded = true;
    paletteLoaded = true;
}

void TerrainGen::create_sprites(){
    if(spriteCreated || !textureLoaded || !paletteLoaded){
        NF_Error(6005, "asd", 4);
    }
    for(int i = 0; i < SPRITE_AMMOUNT; i++){
        // Utilise toujours la palette zéro
        NF_Create3dSprite(i, 0, 0, -128 + (i%4)*128, -160 + (i/4)*128);
    }
    spriteCreated = true;
}

void TerrainGen::delete_sprites(){
    if(!spriteCreated){
        NF_Error(6007, "asd", 4);
    }
    for(int i = 0; i < SPRITE_AMMOUNT; i++){
        NF_Delete3dSprite(i);
    }
    spriteCreated = false;
}

void TerrainGen::unload_textures_and_palettes(){
    if(!textureLoaded || !paletteLoaded || spriteCreated){
        NF_Error(6008, "ASD", 4);
    }
    for(int i = 0; i < TEXTURE_AMMOUNT; i++){
        NF_Free3dSpriteGfx(i);
        NF_UnloadSpriteGfx(i);
    }
    for(int i = 0; i < PALETTE_AMMOUNT; i++){
        NF_UnloadSpritePal(i);
    }
    textureLoaded = false;
    paletteLoaded = false;
}

TerrainGen::TerrainGen(std::string filename){
    load_textures_and_palettes(filename);
    //create_sprites();
}

TerrainGen::~TerrainGen(){
    delete_sprites();
    unload_textures_and_palettes();
}

int TerrainGen::get_tile_from_pos(Vector2i pos){
    return abs(((pos.x)*(pos.y))%2);
}

void TerrainGen::update(Vector2i playerPos){
    // playerPos indique la position du joueur par rapport au monde
    // Par rapport au centre de l'écran, le vecteur est nul
    Vector2i tilePos(playerPos.x/128, playerPos.y/128);
    tilePos.x -= 2;
    tilePos.y -= 2;
    for(int i = 0; i < SPRITE_AMMOUNT; i++){
        Vector2i current_tile_pos(tilePos.x+(i%4), tilePos.y+(i/4));
        int tile = get_tile_from_pos(current_tile_pos);
        Vector2i current_screen_pos(-128 + (i%4)*128 - playerPos.x%128, -160 + (i/4)*128 - playerPos.y%128);
        //if(current_screen_pos.x <= -128 || current_screen_pos.x >= 256 || current_screen_pos.y <= -128 || current_screen_pos.y >= 192){
        //    continue;
        //}
        NF_Create3dSprite(i, tile, 0, current_screen_pos.x, current_screen_pos.y);
    }
}
